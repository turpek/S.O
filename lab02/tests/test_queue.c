#include "unity.h"
#include "queue.h"


#define SUCESSO 0    // usado em asserts para queue_append e queue_remove

typedef struct FilaTest_t{
   struct FilaTest_t *prev ;  // ptr para usar cast com queue_t
   struct FilaTest_t *next ;  // ptr para usar cast com queue_t
   int id ;
} FilaTest_t ;

// Ponteiro para o inicio da fila
FilaTest_t *fila1, *fila2;

// Elementos da fila
FilaTest_t item1, item2, item3;

// Inicializa elemento
void item_init(FilaTest_t *item){
   item->prev = NULL;
   item->next = NULL;
   item->id = 0;
}


// Funções auxiliares para os testes
static int elementos_impressos = 0;


static inline int t_queue_append(FilaTest_t **q, FilaTest_t *elem) {
    return queue_append((queue_t **)q, (queue_t *)elem);
}


static inline int t_queue_remove(FilaTest_t **q, FilaTest_t *elem) {
    return queue_remove((queue_t **)q, (queue_t *)elem);
}


static inline int t_queue_size(FilaTest_t *q) {
    return queue_size((queue_t *)q);
}


static inline void t_queue_print(char *name, FilaTest_t *q, void (*print_elem)(void *)) {
    queue_print(name, (queue_t *)q, print_elem);
}


void print_teste(void *ptr) {
    (void)ptr;
    elementos_impressos++;
}


void setUp(void){
   fila1 = NULL;
   fila2 = NULL;

   // Inicializando os elementos
   item_init(&item1);
   item_init(&item2);
   item_init(&item3);

   elementos_impressos = 0;
}

void tearDown(void){}


void test_queue_append_com_fila_NULL(){

   int retorno = t_queue_append(NULL, &item1);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}


void test_queue_append_com_elemento_NULL(){

   int retorno = t_queue_append(&fila1, NULL);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_append_com_fila_e_elemento_NULL(){

   int retorno = t_queue_append(NULL, NULL);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_append_com_fila_vazia(){

   TEST_ASSERT_NULL(fila1);

   int retorno = t_queue_append(&fila1, &item1);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // Testando os nós da fila
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item1);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item1);
}

void test_queue_append_elemento_com_ponteiro_prev_nao_nulo(){
   TEST_ASSERT_NULL(fila1);

   // Força um ponteiro inválido/sujo
   item1.prev = &item2;

   int retorno = t_queue_append(&fila1, &item1);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
   TEST_ASSERT_NULL(fila1);
}

void test_queue_append_elemento_com_ponteiro_next_nao_nulo(){
   TEST_ASSERT_NULL(fila1);

   // Força um ponteiro inválido/sujo
   item1.next = &item2;

   int retorno = t_queue_append(&fila1, &item1);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
   TEST_ASSERT_NULL(fila1);
}

void test_queue_append_com_fila_contendo_um_elemento(){

   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int retorno = t_queue_append(&fila1, &item2);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // Testando se o item1 continua sendo o inicio da fila
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item2);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item2);

   // Testando se o item2 aponta para os nós corretos
   TEST_ASSERT_EQUAL_PTR(item2.next, &item1);
   TEST_ASSERT_EQUAL_PTR(item2.prev, &item1);
}


void test_queue_append_com_fila_contendo_dois_elementos(){

   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   int retorno = t_queue_append(&fila1, &item3);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // Testando se o item1 continua sendo o inicio da fila
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item3);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item2);

   // Testando se o item2 aponta para os nós corretos
   TEST_ASSERT_EQUAL_PTR(item2.next, &item3);
   TEST_ASSERT_EQUAL_PTR(item2.prev, &item1);

   // Testando se o item3 aponta para os nós corretos
   TEST_ASSERT_EQUAL_PTR(item3.next, &item1);
   TEST_ASSERT_EQUAL_PTR(item3.prev, &item2);
}


void test_queue_append_duas_vezes_o_mesmo_elemento(){

   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int retorno = t_queue_append(&fila1, &item1);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}


void test_queue_append_elemento_de_outra_fila(){

   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila2, &item2);
   int retorno = t_queue_append(&fila1, &item2);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}


// Teste para a função queue_size

void test_queue_size_com_fila_vazia() {
   TEST_ASSERT_NULL(fila1);

   int tamanho = t_queue_size(fila1);
   TEST_ASSERT_EQUAL_INT(0, tamanho);
}

void test_queue_size_com_fila_contendo_um_elemento(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int tamanho = t_queue_size(fila1);
   TEST_ASSERT_EQUAL_INT(1, tamanho);
}

void test_queue_size_com_fila_contendo_tres_elementos(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   t_queue_append(&fila1, &item3);

   int tamanho = t_queue_size(fila1);
   TEST_ASSERT_EQUAL_INT(3, tamanho);
}


// Teste para a função queue_print

void test_queue_print_com_fila_vazia() {
   TEST_ASSERT_NULL(fila1);

   t_queue_print("Fila vazia", fila1, print_teste);
   TEST_ASSERT_EQUAL_INT(0, elementos_impressos);
}

void test_queue_print_com_fila_contendo_um_elemento(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);

   t_queue_print("Fila com 1", fila1, print_teste);
   TEST_ASSERT_EQUAL_INT(1, elementos_impressos);
}

void test_queue_print_com_fila_contendo_tres_elementos(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   t_queue_append(&fila1, &item3);

   t_queue_print("Fila com 3", fila1, print_teste);
   TEST_ASSERT_EQUAL_INT(3, elementos_impressos);
}


// Testes para a função queue_remove

void test_queue_remove_com_fila_NULL(){
   int retorno = t_queue_remove(NULL, &item1);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_remove_com_elemento_NULL(){
   t_queue_append(&fila1, &item1);
   int retorno = t_queue_remove(&fila1, NULL);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_remove_com_fila_e_elemento_NULL(){
   int retorno = t_queue_remove(NULL, NULL);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_remove_com_fila_vazia(){
   TEST_ASSERT_NULL(fila1);
   int retorno = t_queue_remove(&fila1, &item1);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_remove_elemento_isolado_fora_da_fila(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int retorno = t_queue_remove(&fila1, &item2);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);
}

void test_queue_remove_elemento_de_outra_fila(){
   TEST_ASSERT_NULL(fila1);
   TEST_ASSERT_NULL(fila2);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila2, &item2);
   int retorno = t_queue_remove(&fila1, &item2);

   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno);

   // Garante que fila1 e fila2 não foram alteradas
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(&item2, fila2);
}

void test_queue_remove_duas_vezes_o_mesmo_elemento(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int retorno1 = t_queue_remove(&fila1, &item1);
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno1);

   int retorno2 = t_queue_remove(&fila1, &item1);
   TEST_ASSERT_LESS_THAN_INT(SUCESSO, retorno2);
}

void test_queue_remove_unico_elemento(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   int retorno = t_queue_remove(&fila1, &item1);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // A fila deve ter ficado vazia
   TEST_ASSERT_NULL(fila1);

   // O elemento removido deve ter ponteiros isolados
   TEST_ASSERT_NULL(item1.prev);
   TEST_ASSERT_NULL(item1.next);
}


void test_queue_remove_primeiro_elemento_de_dois(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);

   int retorno = t_queue_remove(&fila1, &item1);

   // Testando o retorno
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // O início da fila agora deve ser o item2
   TEST_ASSERT_EQUAL_PTR(&item2, fila1);

   // O nó restante (item2) deve apontar para si mesmo em ambos os sentidos
   TEST_ASSERT_EQUAL_PTR(&item2, fila1->next);
   TEST_ASSERT_EQUAL_PTR(&item2, fila1->prev);

   // O elemento removido deve ter os ponteiros limpos (isolado)
   TEST_ASSERT_NULL(item1.prev);
   TEST_ASSERT_NULL(item1.next);
}

void test_queue_remove_segundo_elemento_de_dois(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);

   int retorno = t_queue_remove(&fila1, &item2);

   // Testando o retorno
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // O início da fila continua sendo o item1
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);

   // O nó restante (item1) deve apontar para si mesmo em ambos os sentidos
   TEST_ASSERT_EQUAL_PTR(&item1, fila1->next);
   TEST_ASSERT_EQUAL_PTR(&item1, fila1->prev);

   // O elemento removido deve ter os ponteiros limpos (isolado)
   TEST_ASSERT_NULL(item2.prev);
   TEST_ASSERT_NULL(item2.next);
}

void test_queue_remove_primeiro_elemento_de_tres(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   t_queue_append(&fila1, &item3);

   int retorno = t_queue_remove(&fila1, &item1);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // O início da fila agora deve ser o item2
   TEST_ASSERT_EQUAL_PTR(&item2, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item3);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item3);

   // Testando as ligações do item3 com item2
   TEST_ASSERT_EQUAL_PTR(item3.next, &item2);
   TEST_ASSERT_EQUAL_PTR(item3.prev, &item2);

   // O elemento removido deve ter ponteiros isolados
   TEST_ASSERT_NULL(item1.prev);
   TEST_ASSERT_NULL(item1.next);
}

void test_queue_remove_ultimo_elemento_de_tres(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   t_queue_append(&fila1, &item3);

   int retorno = t_queue_remove(&fila1, &item3);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // O início da fila continua sendo o item1
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item2);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item2);

   // Testando as ligações do item2 com item1
   TEST_ASSERT_EQUAL_PTR(item2.next, &item1);
   TEST_ASSERT_EQUAL_PTR(item2.prev, &item1);

   // O elemento removido deve ter ponteiros isolados
   TEST_ASSERT_NULL(item3.prev);
   TEST_ASSERT_NULL(item3.next);
}

void test_queue_remove_elemento_do_meio(){
   TEST_ASSERT_NULL(fila1);

   t_queue_append(&fila1, &item1);
   t_queue_append(&fila1, &item2);
   t_queue_append(&fila1, &item3);

   int retorno = t_queue_remove(&fila1, &item2);

   // Testando o retorno da função
   TEST_ASSERT_EQUAL_INT(SUCESSO, retorno);

   // O início da fila continua sendo o item1
   TEST_ASSERT_EQUAL_PTR(&item1, fila1);
   TEST_ASSERT_EQUAL_PTR(fila1->prev, &item3);
   TEST_ASSERT_EQUAL_PTR(fila1->next, &item3);

   // Testando as ligações do item3 com item1
   TEST_ASSERT_EQUAL_PTR(item3.next, &item1);
   TEST_ASSERT_EQUAL_PTR(item3.prev, &item1);

   // O elemento removido deve ter ponteiros isolados
   TEST_ASSERT_NULL(item2.prev);
   TEST_ASSERT_NULL(item2.next);
}


int main(){
  UNITY_BEGIN();

  // Testando a função queue_append
  RUN_TEST(test_queue_append_com_fila_NULL);
  RUN_TEST(test_queue_append_com_elemento_NULL);
  RUN_TEST(test_queue_append_com_fila_e_elemento_NULL);
  RUN_TEST(test_queue_append_elemento_com_ponteiro_prev_nao_nulo);
  RUN_TEST(test_queue_append_elemento_com_ponteiro_next_nao_nulo);
  RUN_TEST(test_queue_append_com_fila_vazia);
  RUN_TEST(test_queue_append_com_fila_contendo_um_elemento);
  RUN_TEST(test_queue_append_com_fila_contendo_dois_elementos);
  RUN_TEST(test_queue_append_duas_vezes_o_mesmo_elemento);
  RUN_TEST(test_queue_append_elemento_de_outra_fila);

  // Testando a função queue_size
  // RUN_TEST(test_queue_size_com_fila_vazia);
  // RUN_TEST(test_queue_size_com_fila_contendo_um_elemento);
  // RUN_TEST(test_queue_size_com_fila_contendo_tres_elementos);

  // // Testando a função queue_print
  // RUN_TEST(test_queue_print_com_fila_vazia);
  // RUN_TEST(test_queue_print_com_fila_contendo_um_elemento);
  // RUN_TEST(test_queue_print_com_fila_contendo_tres_elementos);


  // // --- Casos de Erro / Validações de Parâmetros (< 0) ---
  // RUN_TEST(test_queue_remove_com_fila_NULL);
  // RUN_TEST(test_queue_remove_com_elemento_NULL);
  // RUN_TEST(test_queue_remove_com_fila_e_elemento_NULL);
  // RUN_TEST(test_queue_remove_com_fila_vazia);
  // RUN_TEST(test_queue_remove_elemento_isolado_fora_da_fila);
  // RUN_TEST(test_queue_remove_elemento_de_outra_fila);
  // RUN_TEST(test_queue_remove_duas_vezes_o_mesmo_elemento);

  // --- Casos de Sucesso (Retorno 0) ---
  // RUN_TEST(test_queue_remove_unico_elemento);
  // RUN_TEST(test_queue_remove_primeiro_elemento_de_dois);
  // RUN_TEST(test_queue_remove_segundo_elemento_de_dois);
  // RUN_TEST(test_queue_remove_primeiro_elemento_de_tres);
  // RUN_TEST(test_queue_remove_ultimo_elemento_de_tres);
  // RUN_TEST(test_queue_remove_elemento_do_meio);

  return UNITY_END();
}
