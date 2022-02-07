#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *passenger_name;
    char *priority;

}passenger;

typedef struct{
    char *flight_name;
    int is_closed; //if is_closed equal 0 flight is open

    passenger **business_seats_stack; // it holds empty or full business seats
    int size_of_business_seats_stack;
    int top_of_business_seats_stack;
    passenger **economy_seats_stack; // it holds empty or full economy seats
    int top_of_economy_seats_stack;
    int size_of_economy_seats_stack;
    passenger **standard_seats_stack; // it holds empty or full standard seats
    int top_of_standard_seats_stack;
    int size_of_standard_seats_stack;

    passenger **business_queue;  // it holds enqueue passengers
    int front_of_business_queue;
    int rear_of_business_queue;
    passenger **business_priority_queue; // it holds enqueue passengers
    int front_of_business_priority_queue;
    int rear_of_business_priority_queue;
    passenger **economy_queue;  // it holds enqueue passengers
    int front_of_economy_queue;
    int rear_of_economy_queue;
    passenger **economy_priority_queue;  // it holds enqueue passengers
    int front_of_economy_priority_queue;
    int rear_of_economy_priority_queue;
    passenger **standard_queue; // it holds enqueue passengers
    int front_of_standard_queue;
    int rear_of_standard_queue;

}flight;


int main(int argc, char *argv[]) {
    int i;
    int j;
    int k;
    int m;
    int n;
    int l;
    int i1;
    int j1;
    int k1;
    int o;
    int y;
    int l1;

    FILE *ptr_commands = fopen(argv[1], "r");


    freopen(*(argv+2),"w",stdout); //this line put all stdout output to txt

    if (ptr_commands != NULL) {}
    else {
        printf("failed to open %s\n", argv[1]);
        fclose(ptr_commands);
    }

    fseek(ptr_commands, 0, SEEK_END);
    int commands_file_counter = ftell(ptr_commands); //calculate total byte of all input file
    fseek(ptr_commands, 0, SEEK_SET);


    char c;
    int counter = 0;

    char *file = calloc(commands_file_counter, sizeof(char));

    while ((c = fgetc(ptr_commands)) != EOF) {

        if (c == ' ') {
            while (c == '\n' || c == ' ') {
                while (c == '\n') {
                    c = fgetc(ptr_commands);
                }
                while (c == ' ') {
                    c = fgetc(ptr_commands);
                }
            }
            if (c == EOF) {
                break;
            }
            file[counter] = ' ';
            counter++;
        }
        if (c != ' ') {
            file[counter] = c;
            counter++;
        }
    }
    file[counter] = '\n';

    char *parsed_line;
    parsed_line = strtok(file, "\n");

    flight **ptr_flights = (flight **) malloc(sizeof(flight *));
    int flight_counter = 0;

    while (parsed_line != NULL) {

        char *word_of_command_line;


        while ((word_of_command_line = strsep(&parsed_line, " ")) != NULL) {
            if (strncmp(word_of_command_line, "addseat", strlen("addseat")) == 0) {
                word_of_command_line = strsep(&parsed_line, " ");
                int flight_exist = 0; //if flight doesn't exist in ptr_flight , flight_exist equal 0 otherwise equal 1
                //if flight_exist equal 0 program create new flight

                for (i=0; i < flight_counter; ++i) {
                    if (strncmp(ptr_flights[i]->flight_name, word_of_command_line, strlen(word_of_command_line)) == 0) {
                        flight_exist = 1;
                        if(ptr_flights[i]->is_closed==0) {
                            word_of_command_line = strsep(&parsed_line, " ");
                            if (strncmp(word_of_command_line, "business", strlen("business")) == 0) {
                                word_of_command_line = strsep(&parsed_line, " ");
                                int new_seats_number = atoi(word_of_command_line);

                                ptr_flights[i]->size_of_business_seats_stack += new_seats_number;

                                printf("addseats %s %d %d %d\n",ptr_flights[i]->flight_name,ptr_flights[i]->size_of_business_seats_stack,ptr_flights[i]->size_of_economy_seats_stack,ptr_flights[i]->size_of_standard_seats_stack);

                            } else if (strncmp(word_of_command_line, "economy", strlen("economy")) == 0) {
                                word_of_command_line = strsep(&parsed_line, " ");
                                int new_seats_number = atoi(word_of_command_line);

                                ptr_flights[i]->size_of_economy_seats_stack += new_seats_number;

                                printf("addseats %s %d %d %d\n",ptr_flights[i]->flight_name,ptr_flights[i]->size_of_business_seats_stack,ptr_flights[i]->size_of_economy_seats_stack,ptr_flights[i]->size_of_standard_seats_stack);

                            } else if (strncmp(word_of_command_line, "standard", strlen("standard")) == 0) {
                                word_of_command_line = strsep(&parsed_line, " ");
                                int new_seats_number = atoi(word_of_command_line);

                                ptr_flights[i]->size_of_standard_seats_stack += new_seats_number;
                                printf("addseats %s %d %d %d\n",ptr_flights[i]->flight_name,ptr_flights[i]->size_of_business_seats_stack,ptr_flights[i]->size_of_economy_seats_stack,ptr_flights[i]->size_of_standard_seats_stack);

                            }
                        }

                    }

                }
                if (flight_exist == 0) {
                    ptr_flights[flight_counter] = (flight *) malloc(sizeof(char) + sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int)
                                                                    + sizeof(passenger **) + sizeof(int) +
                                                                    sizeof(int));
                    ptr_flights[flight_counter]->flight_name = malloc(strlen(word_of_command_line) * sizeof(char));
                    strcpy(ptr_flights[flight_counter]->flight_name, word_of_command_line);

                    ptr_flights[flight_counter]->is_closed=0;

                    ptr_flights[flight_counter]->business_seats_stack = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->size_of_business_seats_stack = 0;
                    ptr_flights[flight_counter]->top_of_business_seats_stack = 0;
                    ptr_flights[flight_counter]->economy_seats_stack = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->size_of_economy_seats_stack = 0;
                    ptr_flights[flight_counter]->top_of_economy_seats_stack = 0;
                    ptr_flights[flight_counter]->standard_seats_stack = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->size_of_standard_seats_stack = 0;
                    ptr_flights[flight_counter]->top_of_standard_seats_stack = 0;


                    ptr_flights[flight_counter]->business_queue = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->front_of_business_queue = 0;
                    ptr_flights[flight_counter]->rear_of_business_queue = 0;
                    ptr_flights[flight_counter]->business_priority_queue = (passenger **) malloc(
                            sizeof(passenger *));
                    ptr_flights[flight_counter]->front_of_business_priority_queue = 0;
                    ptr_flights[flight_counter]->rear_of_business_priority_queue = 0;
                    ptr_flights[flight_counter]->economy_queue = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->front_of_economy_queue = 0;
                    ptr_flights[flight_counter]->rear_of_economy_queue = 0;
                    ptr_flights[flight_counter]->economy_priority_queue = (passenger **) malloc(
                            sizeof(passenger *));
                    ptr_flights[flight_counter]->front_of_economy_priority_queue = 0;
                    ptr_flights[flight_counter]->rear_of_economy_priority_queue = 0;
                    ptr_flights[flight_counter]->standard_queue = (passenger **) malloc(sizeof(passenger *));
                    ptr_flights[flight_counter]->front_of_standard_queue = 0;
                    ptr_flights[flight_counter]->rear_of_standard_queue = 0;

                    word_of_command_line = strsep(&parsed_line, " ");
                    if (strncmp(word_of_command_line, "business", strlen("business")) == 0) {
                        word_of_command_line = strsep(&parsed_line, " ");
                        int number_of_seats = atoi(word_of_command_line);
                        ptr_flights[flight_counter]->size_of_business_seats_stack += number_of_seats;

                        printf("addseats %s %d %d %d\n",ptr_flights[flight_counter]->flight_name,ptr_flights[flight_counter]->size_of_business_seats_stack,ptr_flights[flight_counter]->size_of_economy_seats_stack,ptr_flights[flight_counter]->size_of_standard_seats_stack);
                    } else if (strncmp(word_of_command_line, "economy", strlen("economy")) == 0) {
                        word_of_command_line = strsep(&parsed_line, " ");
                        int number_of_seats = atoi(word_of_command_line);
                        ptr_flights[flight_counter]->size_of_economy_seats_stack += number_of_seats;

                        printf("addseats %s %d %d %d\n",ptr_flights[flight_counter]->flight_name,ptr_flights[flight_counter]->size_of_business_seats_stack,ptr_flights[flight_counter]->size_of_economy_seats_stack,ptr_flights[flight_counter]->size_of_standard_seats_stack);
                    } else if (strncmp(word_of_command_line, "standard", strlen("standard")) == 0) {
                        word_of_command_line = strsep(&parsed_line, " ");
                        int number_of_seats = atoi(word_of_command_line);
                        ptr_flights[flight_counter]->size_of_standard_seats_stack += number_of_seats;

                        printf("addseats %s %d %d %d\n",ptr_flights[flight_counter]->flight_name,ptr_flights[flight_counter]->size_of_business_seats_stack,ptr_flights[flight_counter]->size_of_economy_seats_stack,ptr_flights[flight_counter]->size_of_standard_seats_stack);
                    }
                    flight_counter++; // it holds number of flight


                }


            }
            else if(strncmp(word_of_command_line, "enqueue", strlen("enqueue")) == 0) {
                word_of_command_line = strsep(&parsed_line, " ");
                int flight_exist=0;
                for (i = 0; i < flight_counter; ++i) {
                    if(strncmp(ptr_flights[i]->flight_name,word_of_command_line,strlen(word_of_command_line))==0){
                        flight_exist=1;
                        if(ptr_flights[i]->is_closed==0) {
                            word_of_command_line = strsep(&parsed_line, " ");
                            if (strncmp(word_of_command_line, "business", strlen("business")) == 0) {
                                char *name = strsep(&parsed_line, " ");
                                char *priority = strsep(&parsed_line, " ");

                                if (priority == NULL) {
                                    ptr_flights[i]->business_queue = (passenger **) realloc(
                                            ptr_flights[i]->business_queue,
                                            sizeof(passenger *) * (ptr_flights[i]->rear_of_business_queue + 1));
                                    ptr_flights[i]->business_queue[ptr_flights[i]->rear_of_business_queue] = (passenger *) malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->business_queue[ptr_flights[i]->rear_of_business_queue]->passenger_name = malloc(
                                            sizeof(char) * strlen(name));
                                    strcpy(ptr_flights[i]->business_queue[ptr_flights[i]->rear_of_business_queue]->passenger_name,
                                           name);
                                    ptr_flights[i]->business_queue[ptr_flights[i]->rear_of_business_queue]->priority = NULL;
                                    ptr_flights[i]->rear_of_business_queue++;
                                    printf("queue %s %s business %d\n",ptr_flights[i]->flight_name,name,ptr_flights[i]->rear_of_business_priority_queue+ptr_flights[i]->rear_of_business_queue);
                                } else if (strncmp(priority, "diplomat", strlen("diplomat")) == 0) {
                                    ptr_flights[i]->business_priority_queue = (passenger **) realloc(
                                            ptr_flights[i]->business_priority_queue, sizeof(passenger *) *
                                                                                     (ptr_flights[i]->rear_of_business_priority_queue +
                                                                                      1));
                                    ptr_flights[i]->business_priority_queue[ptr_flights[i]->rear_of_business_priority_queue] = (passenger *) malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->business_priority_queue[ptr_flights[i]->rear_of_business_priority_queue]->passenger_name = malloc(
                                            sizeof(char) * strlen(name));
                                    strcpy(ptr_flights[i]->business_priority_queue[ptr_flights[i]->rear_of_business_priority_queue]->passenger_name,
                                           name);
                                    ptr_flights[i]->business_priority_queue[ptr_flights[i]->rear_of_business_priority_queue]->priority = malloc(
                                            sizeof(char) * strlen("diplomat"));
                                    strcpy(ptr_flights[i]->business_priority_queue[ptr_flights[i]->rear_of_business_priority_queue]->priority,
                                           "diplomat");
                                    ptr_flights[i]->rear_of_business_priority_queue++;
                                    printf("queue %s %s business %d\n",ptr_flights[i]->flight_name,name,ptr_flights[i]->rear_of_business_priority_queue+ptr_flights[i]->rear_of_business_queue);
                                }else {
                                    printf("error\n");
                                }
                            } else if (strncmp(word_of_command_line, "economy", strlen("economy")) == 0) {
                                char *name = strsep(&parsed_line, " ");
                                char *priority = strsep(&parsed_line, " ");

                                if (priority == NULL) {
                                    ptr_flights[i]->economy_queue = (passenger **) realloc(
                                            ptr_flights[i]->economy_queue,
                                            sizeof(passenger *) * (ptr_flights[i]->rear_of_economy_queue + 1));
                                    ptr_flights[i]->economy_queue[ptr_flights[i]->rear_of_economy_queue] = (passenger *) malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->economy_queue[ptr_flights[i]->rear_of_economy_queue]->passenger_name = malloc(
                                            sizeof(char) * strlen(name));
                                    strcpy(ptr_flights[i]->economy_queue[ptr_flights[i]->rear_of_economy_queue]->passenger_name,
                                           name);
                                    ptr_flights[i]->economy_queue[ptr_flights[i]->rear_of_economy_queue]->priority = NULL;
                                    ptr_flights[i]->rear_of_economy_queue++;
                                    printf("queue %s %s economy %d\n",ptr_flights[i]->flight_name,name,ptr_flights[i]->rear_of_economy_priority_queue+ptr_flights[i]->rear_of_economy_queue);
                                } else if (strncmp(priority, "veteran", strlen("veteran")) == 0) {
                                    ptr_flights[i]->economy_priority_queue = (passenger **) realloc(
                                            ptr_flights[i]->economy_priority_queue,
                                            sizeof(passenger *) * (ptr_flights[i]->rear_of_economy_priority_queue + 1));
                                    ptr_flights[i]->economy_priority_queue[ptr_flights[i]->rear_of_economy_priority_queue] = (passenger *) malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->economy_priority_queue[ptr_flights[i]->rear_of_economy_priority_queue]->passenger_name = malloc(
                                            sizeof(char) * strlen(name));
                                    strcpy(ptr_flights[i]->economy_priority_queue[ptr_flights[i]->rear_of_economy_priority_queue]->passenger_name,
                                           name);
                                    ptr_flights[i]->economy_priority_queue[ptr_flights[i]->rear_of_economy_priority_queue]->priority = malloc(
                                            sizeof(char) * strlen("veteran"));
                                    strcpy(ptr_flights[i]->economy_priority_queue[ptr_flights[i]->rear_of_economy_priority_queue]->priority,
                                           "veteran");
                                    ptr_flights[i]->rear_of_economy_priority_queue++;
                                    printf("queue %s %s economy %d\n",ptr_flights[i]->flight_name,name,ptr_flights[i]->rear_of_economy_priority_queue+ptr_flights[i]->rear_of_economy_queue);
                                } else {
                                    printf("error\n");
                                }
                            } else if (strncmp(word_of_command_line, "standard", strlen("standard")) == 0) {
                                char *name = strsep(&parsed_line, " ");
                                char *priority = strsep(&parsed_line, " ");

                                if (priority == NULL) {
                                    ptr_flights[i]->standard_queue = (passenger **) realloc(
                                            ptr_flights[i]->standard_queue,
                                            sizeof(passenger *) * (ptr_flights[i]->rear_of_standard_queue + 1));
                                    ptr_flights[i]->standard_queue[ptr_flights[i]->rear_of_standard_queue] = (passenger *) malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_queue[ptr_flights[i]->rear_of_standard_queue]->passenger_name = malloc(
                                            sizeof(char) * strlen(name));
                                    strcpy(ptr_flights[i]->standard_queue[ptr_flights[i]->rear_of_standard_queue]->passenger_name,
                                           name);
                                    ptr_flights[i]->standard_queue[ptr_flights[i]->rear_of_standard_queue]->priority = NULL;
                                    ptr_flights[i]->rear_of_standard_queue++;
                                    printf("queue %s %s standard %d\n",ptr_flights[i]->flight_name,name,ptr_flights[i]->rear_of_standard_queue);
                                } else {
                                    printf("error\n");
                                }
                            }
                        }
                    }

                }
                if(flight_exist==0){
                    printf("error\n");
                }

            }
            else if(strncmp(word_of_command_line, "sell", strlen("sell")) == 0) {
                word_of_command_line = strsep(&parsed_line," ");

                for (i = 0; i < flight_counter; ++i) {
                    if(strncmp(ptr_flights[i]->flight_name,word_of_command_line,strlen(word_of_command_line))==0) {
                        if(ptr_flights[i]->is_closed==0) {
                            for (j = ptr_flights[i]->front_of_business_priority_queue;
                                 j < ptr_flights[i]->rear_of_business_priority_queue; ++j) {
                                if (ptr_flights[i]->size_of_business_seats_stack >
                                    ptr_flights[i]->top_of_business_seats_stack) {


                                    ptr_flights[i]->business_seats_stack = realloc(ptr_flights[i]->business_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_business_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->passenger_name = malloc(
                                            sizeof(char) *
                                            strlen(ptr_flights[i]->business_priority_queue[j]->passenger_name));
                                    strcpy(ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->passenger_name,
                                           ptr_flights[i]->business_priority_queue[j]->passenger_name);
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->priority = malloc(
                                            sizeof(char) * strlen("diplomat"));
                                    strcpy(ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->priority,
                                           "diplomat");

                                    ptr_flights[i]->top_of_business_seats_stack++;
                                    ptr_flights[i]->front_of_business_priority_queue++;
                                }

                            }
                            for (k = ptr_flights[i]->front_of_business_queue;
                                 k < ptr_flights[i]->rear_of_business_queue; ++k) {
                                if (ptr_flights[i]->size_of_business_seats_stack >
                                    (ptr_flights[i]->front_of_business_queue +
                                     ptr_flights[i]->front_of_business_priority_queue)) {

                                    ptr_flights[i]->business_seats_stack = realloc(ptr_flights[i]->business_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_business_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->passenger_name = malloc(
                                            sizeof(char) * strlen(ptr_flights[i]->business_queue[k]->passenger_name));
                                    strcpy(ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->passenger_name,
                                           ptr_flights[i]->business_queue[k]->passenger_name);
                                    ptr_flights[i]->business_seats_stack[ptr_flights[i]->top_of_business_seats_stack]->priority = NULL;

                                    ptr_flights[i]->top_of_business_seats_stack++;
                                    ptr_flights[i]->front_of_business_queue++;
                                }

                            }
                            for (m = ptr_flights[i]->front_of_economy_priority_queue;
                                 m < ptr_flights[i]->rear_of_economy_priority_queue; ++m) {
                                if (ptr_flights[i]->size_of_economy_seats_stack >
                                    ptr_flights[i]->front_of_economy_priority_queue) {

                                    ptr_flights[i]->economy_seats_stack = realloc(ptr_flights[i]->economy_seats_stack,
                                                                                  sizeof(passenger *) *
                                                                                  (ptr_flights[i]->top_of_economy_seats_stack +
                                                                                   1));
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->passenger_name = malloc(
                                            sizeof(char) *
                                            strlen(ptr_flights[i]->economy_priority_queue[m]->passenger_name));
                                    strcpy(ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->passenger_name,
                                           ptr_flights[i]->economy_priority_queue[m]->passenger_name);
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->priority = malloc(
                                            sizeof(char) * strlen("veteran"));
                                    strcpy(ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->priority,
                                           "veteran");


                                    ptr_flights[i]->top_of_economy_seats_stack++;
                                    ptr_flights[i]->front_of_economy_priority_queue++;
                                }

                            }

                            for (n = ptr_flights[i]->front_of_economy_queue;
                                 n < ptr_flights[i]->rear_of_economy_queue; ++n) {
                                if (ptr_flights[i]->size_of_economy_seats_stack >
                                    ptr_flights[i]->front_of_economy_queue +
                                    ptr_flights[i]->front_of_economy_priority_queue) {

                                    ptr_flights[i]->economy_seats_stack = realloc(ptr_flights[i]->economy_seats_stack,
                                                                                  sizeof(passenger *) *
                                                                                  (ptr_flights[i]->top_of_economy_seats_stack +
                                                                                   1));
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->passenger_name = malloc(
                                            sizeof(char) * strlen(ptr_flights[i]->economy_queue[n]->passenger_name));
                                    strcpy(ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->passenger_name,
                                           ptr_flights[i]->economy_queue[n]->passenger_name);
                                    ptr_flights[i]->economy_seats_stack[ptr_flights[i]->top_of_economy_seats_stack]->priority = NULL; //if doesn't exist passengers priority equal NULL

                                    ptr_flights[i]->top_of_economy_seats_stack++;
                                    ptr_flights[i]->front_of_economy_queue++;
                                }

                            }
                            for (l = ptr_flights[i]->front_of_standard_queue;
                                 l < ptr_flights[i]->rear_of_standard_queue; ++l) {
                                if (ptr_flights[i]->size_of_standard_seats_stack >
                                    ptr_flights[i]->front_of_standard_queue) {

                                    ptr_flights[i]->standard_seats_stack = realloc(ptr_flights[i]->standard_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_standard_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name = malloc(
                                            sizeof(char) * strlen(ptr_flights[i]->standard_queue[l]->passenger_name));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name,
                                           ptr_flights[i]->standard_queue[l]->passenger_name);
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority = NULL;

                                    ptr_flights[i]->top_of_standard_seats_stack++;
                                    ptr_flights[i]->front_of_standard_queue++;
                                }


                            }
                            for (i1 = ptr_flights[i]->front_of_business_priority_queue;
                                 i1 < ptr_flights[i]->rear_of_business_priority_queue; ++i1) {
                                if (ptr_flights[i]->size_of_standard_seats_stack >
                                    ptr_flights[i]->top_of_standard_seats_stack) {


                                    ptr_flights[i]->standard_seats_stack = realloc(ptr_flights[i]->standard_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_standard_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name = malloc(
                                            sizeof(char) *
                                            strlen(ptr_flights[i]->business_priority_queue[i1]->passenger_name));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name,
                                           ptr_flights[i]->business_priority_queue[i1]->passenger_name);
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority = malloc(
                                            sizeof(char) * strlen("diplomat"));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority,
                                           "diplomat");

                                    ptr_flights[i]->top_of_standard_seats_stack++;
                                    ptr_flights[i]->front_of_business_priority_queue++;
                                }

                            }
                            for (j1 = ptr_flights[i]->front_of_business_queue;
                                 j1 < ptr_flights[i]->rear_of_business_queue; ++j1) {
                                if (ptr_flights[i]->size_of_standard_seats_stack >
                                    ptr_flights[i]->top_of_standard_seats_stack) {


                                    ptr_flights[i]->standard_seats_stack = realloc(ptr_flights[i]->standard_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_standard_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name = malloc(
                                            sizeof(char) * strlen(ptr_flights[i]->business_queue[j1]->passenger_name));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name,
                                           ptr_flights[i]->business_queue[j1]->passenger_name);
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority = NULL;

                                    ptr_flights[i]->top_of_standard_seats_stack++;
                                    ptr_flights[i]->front_of_business_queue++;
                                }

                            }
                            for (k1 = ptr_flights[i]->front_of_economy_priority_queue;
                                 k1 < ptr_flights[i]->rear_of_economy_priority_queue; ++k1) {
                                if (ptr_flights[i]->size_of_standard_seats_stack >
                                    ptr_flights[i]->top_of_standard_seats_stack) {


                                    ptr_flights[i]->standard_seats_stack = realloc(ptr_flights[i]->standard_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_standard_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name = malloc(
                                            sizeof(char) *
                                            strlen(ptr_flights[i]->economy_priority_queue[k1]->passenger_name));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name,
                                           ptr_flights[i]->economy_priority_queue[k1]->passenger_name);
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority = malloc(
                                            sizeof(char) * strlen("veteran"));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority,
                                           "veteran");

                                    ptr_flights[i]->top_of_standard_seats_stack++;
                                    ptr_flights[i]->front_of_economy_priority_queue++;
                                }

                            }
                            for (j1 = ptr_flights[i]->front_of_economy_queue;
                                 j1 < ptr_flights[i]->rear_of_economy_queue; ++j1) {
                                if (ptr_flights[i]->size_of_standard_seats_stack >
                                    ptr_flights[i]->top_of_standard_seats_stack) {


                                    ptr_flights[i]->standard_seats_stack = realloc(ptr_flights[i]->standard_seats_stack,
                                                                                   sizeof(passenger *) *
                                                                                   (ptr_flights[i]->top_of_standard_seats_stack +
                                                                                    1));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack] = malloc(
                                            sizeof(char) + sizeof(char));
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name = malloc(
                                            sizeof(char) * strlen(ptr_flights[i]->economy_queue[j1]->passenger_name));
                                    strcpy(ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->passenger_name,
                                           ptr_flights[i]->economy_queue[j1]->passenger_name);
                                    ptr_flights[i]->standard_seats_stack[ptr_flights[i]->top_of_standard_seats_stack]->priority = NULL;

                                    ptr_flights[i]->top_of_standard_seats_stack++;
                                    ptr_flights[i]->front_of_economy_queue++;
                                }

                            }
                            printf("sold %s %d %d %d\n",ptr_flights[i]->flight_name,ptr_flights[i]->top_of_business_seats_stack,ptr_flights[i]->top_of_economy_seats_stack,ptr_flights[i]->top_of_standard_seats_stack);
                        }
                        else{
                            printf("error\n");
                        }
                    }
                }
            }
            else if(strncmp(word_of_command_line, "close", strlen("close")) == 0) {
                word_of_command_line = strsep(&parsed_line, " ");
                for (i = 0; i < flight_counter; ++i) {
                    if(strncmp(ptr_flights[i]->flight_name,word_of_command_line,strlen(word_of_command_line))==0){
                        ptr_flights[i]->is_closed=1;
                        printf("closed %s %d %d\n",ptr_flights[i]->flight_name,ptr_flights[i]->top_of_standard_seats_stack+ptr_flights[i]->top_of_economy_seats_stack+ptr_flights[i]->top_of_business_seats_stack,
                               ptr_flights[i]->rear_of_economy_queue+ptr_flights[i]->rear_of_economy_priority_queue+ptr_flights[i]->rear_of_business_priority_queue+ptr_flights[i]->rear_of_business_queue+
                               ptr_flights[i]->rear_of_standard_queue-ptr_flights[i]->front_of_business_priority_queue-ptr_flights[i]->front_of_economy_queue-ptr_flights[i]->front_of_economy_priority_queue-
                               ptr_flights[i]->front_of_business_queue-ptr_flights[i]->front_of_standard_queue);
                        for (j = ptr_flights[i]->front_of_business_priority_queue; j < ptr_flights[i]->rear_of_business_priority_queue; ++j) {
                            printf("waiting %s\n",ptr_flights[i]->business_priority_queue[j]->passenger_name);
                        }
                        for (k = ptr_flights[i]->front_of_business_queue; k < ptr_flights[i]->rear_of_business_queue; ++k) {
                            printf("waiting %s\n",ptr_flights[i]->business_queue[k]->passenger_name);
                        }
                        for (l = ptr_flights[i]->front_of_economy_priority_queue; l < ptr_flights[i]->rear_of_economy_priority_queue; ++l) {
                            printf("waiting %s\n",ptr_flights[i]->economy_priority_queue[l]->passenger_name);
                        }
                        for (m = ptr_flights[i]->front_of_economy_queue; m < ptr_flights[i]->rear_of_economy_queue; ++m) {
                            printf("waiting %s\n",ptr_flights[i]->economy_queue[m]->passenger_name);
                        }
                        for (n = ptr_flights[i]->front_of_standard_queue; n < ptr_flights[i]->rear_of_standard_queue; ++n) {
                            printf("waiting %s\n",ptr_flights[i]->standard_queue[n]->passenger_name);
                        }

                    }
                }
            }
            else if(strncmp(word_of_command_line, "report", strlen("report")) == 0) {
                word_of_command_line = strsep(&parsed_line, " ");
                for (i = 0; i < flight_counter; ++i) {
                    if (strncmp(ptr_flights[i]->flight_name, word_of_command_line, strlen(word_of_command_line)) == 0) {
                        printf("report %s\n",ptr_flights[i]->flight_name);
                        printf("business %d\n",ptr_flights[i]->top_of_business_seats_stack);
                        for (j = 0; j < ptr_flights[i]->top_of_business_seats_stack; ++j) {
                            printf("%s\n",ptr_flights[i]->business_seats_stack[j]->passenger_name);
                        }
                        printf("economy %d\n",ptr_flights[i]->top_of_economy_seats_stack);
                        for (o = 0; o < ptr_flights[i]->top_of_economy_seats_stack; ++o) {
                            printf("%s\n",ptr_flights[i]->economy_seats_stack[o]->passenger_name);
                        }
                        printf("standard %d\n",ptr_flights[i]->top_of_standard_seats_stack);
                        for (y = 0; y < ptr_flights[i]->top_of_standard_seats_stack; ++y) {
                            printf("%s\n",ptr_flights[i]->standard_seats_stack[y]->passenger_name);
                        }
                        printf("end of report %s\n",ptr_flights[i]->flight_name);
                    }
                }
            }
            else if(strncmp(word_of_command_line, "info", strlen("info")) == 0) {
                word_of_command_line = strsep(&parsed_line, " ");
                int in_business_queue=0;
                int in_economy_queue=0;
                int in_standard_queue=0;
                int in_business_stack=0;
                int in_economy_stack=0;
                int in_standard_stack=0;
                int is_viewed=0; //this variable is 1 if passenger information is shown
                for (i = 0; i < flight_counter; ++i) {
                    if(is_viewed==0) {
                        in_business_queue = 0;
                        in_economy_queue = 0;
                        in_standard_queue = 0;
                        in_business_stack = 0;
                        in_economy_stack = 0;
                        in_standard_stack = 0;

                        for (j = 0; j < ptr_flights[i]->rear_of_business_priority_queue; ++j) {
                            if (strncmp(ptr_flights[i]->business_priority_queue[j]->passenger_name,
                                        word_of_command_line, strlen(word_of_command_line)) == 0) {
                                in_business_queue = 1;
                            }
                        }
                        for (k = 0; k < ptr_flights[i]->rear_of_business_queue; ++k) {
                            if (strncmp(ptr_flights[i]->business_queue[k]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_business_queue = 1;
                            }
                        }
                        for (j = 0; j < ptr_flights[i]->rear_of_economy_priority_queue; ++j) {
                            if (strncmp(ptr_flights[i]->economy_priority_queue[j]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_economy_queue = 1;
                            }
                        }
                        for (k = 0; k < ptr_flights[i]->rear_of_economy_queue; ++k) {
                            if (strncmp(ptr_flights[i]->economy_queue[k]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_economy_queue = 1;

                            }
                        }
                        for (k = 0; k < ptr_flights[i]->rear_of_standard_queue; ++k) {
                            if (strncmp(ptr_flights[i]->standard_queue[k]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_standard_queue = 1;
                            }
                        }
                        for (l = 0; l < ptr_flights[i]->top_of_business_seats_stack; ++l) {
                            if (strncmp(ptr_flights[i]->business_seats_stack[l]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_business_stack = 1;
                            }
                        }
                        for (l = 0; l < ptr_flights[i]->top_of_economy_seats_stack; ++l) {
                            if (strncmp(ptr_flights[i]->economy_seats_stack[l]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_economy_stack = 1;
                            }
                        }
                        for (l = 0; l < ptr_flights[i]->top_of_standard_seats_stack; ++l) {
                            if (strncmp(ptr_flights[i]->standard_seats_stack[l]->passenger_name, word_of_command_line,
                                        strlen(word_of_command_line)) == 0) {
                                in_standard_stack = 1;
                            }
                        }
                        if (in_business_queue == 1) {
                            if (in_business_stack == 1) {
                                printf("info %s %s business business\n", word_of_command_line,
                                       ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            } else if (in_standard_stack == 1) {
                                printf("info %s %s business standard\n", word_of_command_line,
                                       ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            } else {
                                printf("info %s %s business none\n", word_of_command_line, ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            }
                        } else if (in_economy_queue == 1) {
                            if (in_economy_stack == 1) {
                                printf("info %s %s economy economy\n", word_of_command_line,
                                       ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            } else if (in_standard_stack == 1) {
                                printf("info %s %s economy standard\n", word_of_command_line,
                                       ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            } else {
                                printf("info %s %s economy none\n", word_of_command_line, ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            }
                        } else if (in_standard_queue == 1) {
                            if (in_standard_stack == 1) {
                                printf("info %s %s standard standard\n", word_of_command_line,
                                       ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            } else {
                                printf("info %s %s standard none\n", word_of_command_line, ptr_flights[i]->flight_name);
                                is_viewed = 1;
                            }
                        }
                    }


                }
                if(is_viewed==0){
                    printf("error\n");
                }
            }


        }


        parsed_line = strtok(NULL, "\n");

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    free(parsed_line);
    free(file);
    for (l1 = 0; l1 <flight_counter ; ++l1) {

        free(ptr_flights[l1]->flight_name);// this free part sometimes print (double free or corruption (out)) error in every way but output doesn't change

        for (i = 0; i < ptr_flights[l1]->rear_of_business_priority_queue; ++i) {
            free(ptr_flights[l1]->business_priority_queue[i]->passenger_name);
            free(ptr_flights[l1]->business_priority_queue[i]->priority);
            free(ptr_flights[l1]->business_priority_queue[i]);
        }
        for (j = 0; j < ptr_flights[l1]->rear_of_business_queue; ++j) {
            free(ptr_flights[l1]->business_queue[j]->passenger_name);
            free(ptr_flights[l1]->business_queue[j]->priority);
            free(ptr_flights[l1]->business_queue[j]);
        }
        for (k = 0; k < ptr_flights[l1]->rear_of_economy_priority_queue; ++k) {
            free(ptr_flights[l1]->economy_priority_queue[k]->passenger_name);
            free(ptr_flights[l1]->economy_priority_queue[k]->priority);
            free(ptr_flights[l1]->economy_priority_queue[k]);
        }
        for (l = 0; l < ptr_flights[l1]->rear_of_economy_queue; ++l) {
            free(ptr_flights[l1]->economy_queue[l]->passenger_name);
            free(ptr_flights[l1]->economy_queue[l]->priority);
            free(ptr_flights[l1]->economy_queue[l]);
        }
        for (m = 0; m < ptr_flights[l1]->rear_of_standard_queue; ++m) {
            free(ptr_flights[l1]->standard_queue[m]->passenger_name);
            free(ptr_flights[l1]->standard_queue[m]->priority);
            free(ptr_flights[l1]->standard_queue[m]);
        }

        for (n = 0; n < ptr_flights[l1]->top_of_business_seats_stack; ++n) {
            free(ptr_flights[l1]->business_seats_stack[n]->passenger_name);
            free(ptr_flights[l1]->business_seats_stack[n]->priority);
            free(ptr_flights[l1]->business_seats_stack[n]);
        }
        for (i1 = 0; i1 < ptr_flights[l1]->top_of_economy_seats_stack; ++i1) {
            free(ptr_flights[l1]->economy_seats_stack[i1]->passenger_name);
            free(ptr_flights[l1]->economy_seats_stack[i1]->priority);
            free(ptr_flights[l1]->economy_seats_stack[i1]);
        }
        for (j1 = 0; j1 < ptr_flights[l1]->top_of_standard_seats_stack; ++j1) {
            free(ptr_flights[l1]->standard_seats_stack[j1]->passenger_name);
            free(ptr_flights[l1]->standard_seats_stack[j1]->priority);
            free(ptr_flights[l1]->standard_seats_stack[j1]);
        }
        free(ptr_flights[l1]->business_priority_queue);
        free(ptr_flights[l1]->business_queue);
        free(ptr_flights[l1]->economy_priority_queue);
        free(ptr_flights[l1]->economy_queue);
        free(ptr_flights[l1]->standard_queue);
        free(ptr_flights[l1]->business_seats_stack);
        free(ptr_flights[l1]->economy_seats_stack);
        free(ptr_flights[l1]->standard_seats_stack);
        free(ptr_flights[l1]);
    }
    free(ptr_flights);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fclose(ptr_commands);
}