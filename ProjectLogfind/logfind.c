/*
 * This is (a small)/(my truly first C) practice program that searches
 * strings in a list of files, where the list itself is in a file and must
 * be provided as a command line argument. Although the name suggests it
 * searches in logfiles only, it is usable for any text file.
 * 
 * The program can take any valid (and invalid) flag in any order, and
 * they can be before, after or even inside the search string.
 * 
 * There are two search modes available:
 * - AND (no additional argument): searches the file(s) and matches
 *      the whole string provided (up to 256-(NumOfArgs) words total
 *      at the time
 * - OR (-o): tries to match any of the words provided in the arguments
 * 
 * Some parts of the program are deliberately designed to be extendable,
 * like code related to argument parsing, so they might seem over-complicated
 * for such simple use.
 * 
 * The loglist file should ONLY contain the path of files to be searched,
 * "comment ignoring" is not implemented. All lines are considered to be
 * file paths right now.
 * 
 * Any suggestions are welcome, so feel free to drop a comment or message.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>


/*
 * Just prints some general help about the usage of this program.
 */
void print_help() {
    printf("Usage: logfind [option] [arg] [words]\n"
            "Options: -h:\tprint this help\n"
            "\t-l:\tloads the log file list\n"
            "\t-o:\tswitches to OR mode\n");
}


/*
 * This holds info of what flags are used by the user and
 * where they are in argv[]. Having uint8_t also means that
 * we only intend to handle less than 256 arguments for now,
 * including flags.
 */
typedef struct Flags {
    uint8_t size;   // Number of flag types we use.
    uint8_t help;   // position of -h in argv[]
    uint8_t loglist;// position of -l in argv[]
    uint8_t turnor; // position of -o in argv[]
} Flags;


/*
 * This helps to iterate through the Flags struct
 */
uint8_t list_flags(Flags* f, int i) {
    switch (i) {
        case 0: return f->help;
        case 1: return f->loglist;
        case 2: return f->turnor;
        default: return 0;
    }
    return 0;
}


/*
 * Checking if we have flags and are in correct configuration.
 * If -h is present, we don't need to go further, just return, as
 * all other args are ignored and only help will be printed.
 * -1 (minus one) indicates error, 0 is OK.
 */
int check_flags(Flags* f) {
    if (f->help) return 0;
    
    int j=0;
    for (j=1; j < f->size; ++j) {
        if(list_flags(f, f->size)) return 0;
    }
    return -1;
}


/*
 * This function tells if num can be found in a Flags struct.
 * Basically this is used to filter out the positions of the
 * flags in argv[]. It also takes flags with additional arguments
 * into account, like -l, thus the position of -l+1 in argv[] is
 * also considered to be used as a flag.
 */
int search_flags(int num, Flags* f) {
    
    /*
     * case: 1 in search_flags is a flag with an additional arg (+1),
     * thus checking for it manually. We don't want this in every
     * iteration of the loop.
    */
    if (num==list_flags(f,1)+1) return 1;
    
    /*
     * Checking for every other standard flag position.
     */
    int i = 0;
    for(i=0; i < f->size; ++i) {
        if (num==list_flags(f,i)) return 1;
    }
    
    return 0;
}


/*
 * This will set the fields of a Flags struct from argv[] and perform
 * some sanity checks. The flags can be located anywhere in argv[] but
 * can only be one character long and can only be used once. The exact
 * position of flags in argv[] is the value stored in the Flags struct.
 * -1 (minus one) indicates error, 0 is OK
 */
int get_flags(int argc, char* argv[], Flags* f) {
    int i=0;
    while (++i < argc) {
        if (argv[i][0]=='-' && argv[i][2]=='\0') {
            switch (argv[i][1]) {
                case 'h':
                    if(f->help) {
                        fprintf(stderr, "Flag -h used more than once!\n");
                        return -1;
                    }
                    f->help=i;
                    break;
                case 'l':
                    if(f->loglist) {
                        fprintf(stderr, "Flag -l used more than once!\n");
                        return -1;
                    }
                    f->loglist=i;
                    break;
                case 'o':
                    if(f->turnor) {
                        fprintf(stderr, "Flag -o used more than once!\n");
                        return -1;
                    }
                    f->turnor=i;
                    break;
                default:
                    fprintf(stderr, "Invalid argument!\n");
                    return -1;
            }
        }
    }
    return check_flags(f);
}

/*
 * This just counts the total length of all aruments in argv[].
 */
size_t count_len(int argc, char* argv[]) {
    int i=0;
    size_t tot_length=0;
    
    while(++i<argc) {
        // +1 because we will need whitespace between words as well
        tot_length+=strlen(argv[i])+1;
    }
    
    return tot_length;
};


/*
 * Replaces all non-alphanumeric characters with whitespace.
 * Lowercase chars are most common, so we are checking for those
 * first.
 */
void replace_nonalphanum(char* line, ssize_t charnum) {
    int i=0;
    for(i=0; i<charnum; ++i) {
        if ( ('a'<=line[i] && line[i]<='z') || ('A'<=line[i] && line[i]<='Z') ) {
        } else if ('0'<=line[i] && line[i]<='9') {
        } else {
            line[i]=' ';
        }
    }
}


/*
 * This assembles the search string we will need to use to search
 * the log files. The string will not contain flags and corresponding
 * arguments. 
 */
void get_search_string(char* search_string, Flags* currflag, int argc, char* argv[]) {
    int i=0;
    
    while (++i < argc) {
        if(!search_flags(i, currflag)) {
            strcat(search_string, argv[i]);
            strcat(search_string, " ");
        };
    }
}


/*
 * This does the actual comparison of the search_string and a line in a file.
 * If 'mode' is zero (no position for flag -o) it is in AND mode, otherwise OR.
 */
char* compare_str(const char* search_string, const char* line, const uint8_t mode) {
    if(mode==0) {
        return strstr(line, search_string);
    } else {
        uint32_t len=strlen(search_string);
        char* temp_srch=malloc(len+1);
        if (!temp_srch) return NULL;
        
        strcpy(temp_srch, search_string);
        
        char* token=strtok(temp_srch, " ");
        if (!token) {
            free(temp_srch);
            return NULL;
        }
        
        char* retval=NULL;
        
        while(token) {
            retval=strstr(line, temp_srch);
            
            if(retval) {
                free(temp_srch);
                return retval;
            }
            else token=strtok(NULL, " ");
        }
        
        free(temp_srch);
    }
    
    return NULL;
}


/*
 * This looks for the contents of search_string in file by the name of
 * filepath. If argument 'mode' is 0, than we are in AND mode, anything else
 * translates to OR mode. The mode decides if we are looking for the
 * entirety of search_string, or just any word within it.
 */
uint8_t do_search(const char* search_string, const char* filepath, const uint8_t mode){
    uint32_t line_num=0;
    char* found_word=NULL;
    uint8_t found_something=0;
    FILE* logfile = fopen(filepath, "r");
    
    // a missing logfile is not critical, so we simply skip it with an error message.
    if(logfile==NULL) {
        fprintf(stderr, "Could not open %s\n", filepath);
        
    } else {
        char* linebuf=NULL;
        size_t bufsize=0;
        ssize_t charnum=0;
    
        while ( (charnum=getline(&linebuf, &bufsize, logfile)) !=-1) {
            line_num++;
            replace_nonalphanum(linebuf, charnum);
            linebuf[charnum-1]='\0'; // overwriting ending '\n'
            
            if (found_word=compare_str(search_string, linebuf, mode)) {
                printf("%s:%d: %s\n", filepath, line_num, linebuf);
            }
            // it sets the return value found_something.
            if(!found_something && found_word) {
                found_something=1;
            }
        }
        
        free(linebuf);
    }
    
    if(logfile!=NULL) fclose(logfile);
    
    return found_something;
}

/*
 * This searches through all the files listed in the file provided as an
 * argument after -l
 */
void search_files(char* filename, char* search_string, const uint8_t mode) {
    FILE* loglist=NULL;
    
    loglist = fopen(filename, "r");
    if(loglist==NULL) {
        fprintf(stderr, "The log list file \"%s\" not found. Terminating.\n", filename);
    } else {
    
        char* linebuf=NULL;
        size_t bufsize=0;
        ssize_t charnum=0;
        int filecount=0;
    
        while( (charnum=getline(&linebuf, &bufsize, loglist)) !=-1) {
            ++filecount;
            linebuf[charnum-1]='\0';    // overwriting ending '\n'
        
            if (do_search(search_string, linebuf, mode)) {
                printf("Search complete in %s.\n\n", linebuf);
            } else {
                printf("Nothing found in %s.\n\n", linebuf);
            }
        
        }
        
        free(linebuf);
    }
    
    
    if(loglist!=NULL) fclose(loglist);
}


/*
 * This just prints the summary of the task for the user before
 * starting it.
 */
void prnt_task_info(const Flags* f, const char* search_string){
    char* flag_or_mode;
    if(f->turnor) {
        flag_or_mode="OR";
    } else {
        flag_or_mode="AND";
    }
    
    printf("In %s mode, you are looking for: %s \n\n", flag_or_mode, search_string);
}


int main(int argc, char* argv[]){

    Flags currflag = {.size = 3, .help = 0, .loglist = 0, .turnor = 0};
    
    char* search_string=malloc(count_len(argc, argv));
    if (!search_string) {
        fprintf(stderr, "Could not allocate memory. Terminating.\n");
        goto clean_exit;
    }
    
/*
 * get_flags has its own messages, so there is no need to print extra
 * to know what is going on.
 */ 
    if(!argc<=UCHAR_MAX && get_flags(argc, argv, &currflag)) {
        fprintf(stderr, "Something went wrong. Terminating.\n");
        goto clean_exit;
    }
    
    get_search_string(search_string, &currflag, argc, argv);
    
    prnt_task_info(&currflag, search_string);
    
    search_files(argv[currflag.loglist+1], search_string, currflag.turnor);
    
  
clean_exit:
    if (search_string!=NULL) free(search_string);
    return 0;
}
