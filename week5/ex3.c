#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int products_prices_by_items[3];
int number_of_full_items = 0;
int minimal_price = 10;
int maximal_price = 300;
int max_reaction_sec = 2;
int min_reaction_sec = 1;
int producer_reaction_sec = 0;
int consumer_reaction_sec = 0;
int pause_time_sec = 10;
bool is_producer_waiting_for_place = false;
bool is_consumer_waiting_for_products = false;
bool is_modeling_on_action = true;
bool is_producer_sleeping = false;
bool is_consumer_sleeping = false;
bool is_waiting = false;


void print_prices() {
    for (int i = 0; i < sizeof(products_prices_by_items) / sizeof(int); i++) {
        printf("%d ", products_prices_by_items[i]);
    }
    printf("\n");
}

void sleep_producer() {
    is_producer_sleeping = true;
}

void wake_up_producer() {
    is_producer_sleeping = false;
}

void sleep_consumer() {
    is_consumer_sleeping = true;
}

void wake_up_consumer() {
    is_consumer_sleeping = false;
}

int get_new_price() {
    return minimal_price + rand() % (maximal_price - minimal_price + 1);
}

void to_many_products_for_producer() {
    printf ("PRODUCER STARTS SLEEPING now! To many products!\n");
    is_producer_waiting_for_place = true;
    sleep_producer();
}

void new_space_for_products_appeared() {
    printf("PRODUCER WAKES UP! It is time to bring new products!\n");
    is_producer_waiting_for_place = false;
    wake_up_producer();
}

void no_products_for_consumer() {
    printf("CONSUMER STARTS SLEEPING! There are no products in the shop yet!\n");
    is_consumer_waiting_for_products = true;
    sleep_consumer();
}

void new_products_for_consumer() {
    printf("CONSUMER WAKES UP! There are new products in the shop! It is time to buy something!\n");
    is_consumer_waiting_for_products = false;
    wake_up_consumer();
}

void add_new_product(int price) {
    if (number_of_full_items < sizeof(products_prices_by_items) / sizeof(int)) {
        products_prices_by_items[number_of_full_items] = price;
        number_of_full_items++;
        printf("PRODUCER: New product with the PRICE %d! ", price);
        printf("Current prices of products:\n");
        print_prices();
    } else {
        to_many_products_for_producer();
    }
}

void *producer_activity() {
    while (is_modeling_on_action) {
        if (is_waiting) {
            sleep(pause_time_sec);
        }
        if (is_producer_sleeping) {
            continue;
        }
        sleep(producer_reaction_sec);
        if (!is_producer_sleeping) {
            sleep_consumer();
        } else {
            continue;
        }
        if (is_producer_waiting_for_place) {
            new_space_for_products_appeared();
        }
        add_new_product(get_new_price());
        wake_up_consumer();
    }
    printf("Goodbye from Producer! Best wishes!\n");
    pthread_exit(NULL);
}

void buy_product() {
    if (number_of_full_items != 0) {
        printf("CONSUMER: Hey! I'm going to BUY the %d product by the price %d! ", number_of_full_items, 
            products_prices_by_items[number_of_full_items-1]);
        number_of_full_items--;
        products_prices_by_items[number_of_full_items] = 0;
        printf("Current prices of products:\n");
        print_prices();
    } else {
        no_products_for_consumer();
    }
}

void *consumer_activity() {
    while (is_modeling_on_action) {
        if (is_waiting) {
            sleep(pause_time_sec);
        }
        if (is_consumer_sleeping) {
            continue;
        }
        sleep(consumer_reaction_sec);
        if (!is_consumer_sleeping) {
            sleep_producer();
        } else {
            continue;
        }
        if (is_consumer_waiting_for_products) {
            new_products_for_consumer();
        }
        buy_product();
        wake_up_producer();
    }
    printf("Bye from Consumer! Be happy!\n");
    pthread_exit(NULL);
}

void *update_reaction() {
    while(is_modeling_on_action) {
        consumer_reaction_sec = min_reaction_sec + rand() % (max_reaction_sec - min_reaction_sec + 1);
        producer_reaction_sec = min_reaction_sec + rand() % (max_reaction_sec - min_reaction_sec + 1);
    }
    pthread_exit(NULL);
}

int main() {
    printf("Welcome to our shop! Here we have crazy producer and consumer! They are so crazy that will not stop to buy and sell! \n");
    printf("You can stop them only by enter the 's' and then fast press the Enter button!\n");
    printf("To print prices and make a pause enter the 'p' and fast press Enter button! ");
    printf("It will be wait for a %d seconds to see prices.\n", pause_time_sec);
    printf("There is %d items for products. While the process is running guys sell and buy with the different reaction.\n",
        sizeof(products_prices_by_items) / sizeof(int));
    printf("Reactions are not always similar. It changes! Sometimes one of the guys cannot do anything and go to sleep\n");
    printf("Enjoy the show! To start press 'y' on your keyboard: \n");
    char start_command;
    scanf(" %c", &start_command);
    if (start_command != 'y') {
        while (start_command != 'y') {
            printf("Hey! You didn't read it clearly! Please, only 'y' button, nothing else:\n");
            scanf(" %c", &start_command);
        }
    }
    srand(time(NULL));
    pthread_t producer_thread_id;
    pthread_t consumer_thread_id;
    pthread_t reaction_thread_id;
    pthread_create(&reaction_thread_id, NULL, &update_reaction, NULL);
    pthread_create(&producer_thread_id, NULL, &producer_activity, NULL);
    pthread_create(&consumer_thread_id, NULL, &consumer_activity, NULL);
    char stop_command = '.';
    scanf("%c", &stop_command);
    while(stop_command != 's') {
        scanf("%c", &stop_command);
        if (stop_command == 'p') {
            is_waiting = true;
            print_prices();
            sleep(pause_time_sec);
            is_waiting = false;
        }
    }
    is_modeling_on_action = false;
    pthread_exit(NULL);
    return 0;
}