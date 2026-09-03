#include "queue.h"


int queue_append (queue_t **queue, queue_t *elem) {

   if(queue == NULL || elem == NULL) {
      return -1;
   }
   else if(elem->prev != NULL || elem->next != NULL) {
      return -1;
   }
   else if(*queue == NULL) {
      elem->prev = elem;
      elem->next = elem;
      *queue = elem;
      return 0;
   }

   queue_t *first = *queue;
   queue_t *last = first->prev;

   last->next = elem;
   first->prev = elem;

   elem->prev = last;
   elem->next = first;

   return 0;
}

int queue_size (queue_t *queue) {
   return -1;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {

}

int queue_remove (queue_t **queue, queue_t *elem) {
   return 1;
}
