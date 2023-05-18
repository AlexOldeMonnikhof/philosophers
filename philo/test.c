#include <stdio.h>
#include <pthread.h>

void    *asd(void *param)
{
    
}

int main(void)
{
    pthread_t th[2];
    pthread_mutex_t *fork;
    pthread_mutex_init(fork, NULL);
    pthread_create(th[0], NULL, &asd, NULL);
    pthread_create(th[1], NULL, &asd, NULL);

}