#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>

#define DATA_SIZE 100

int main(){
	int shmid, shmid2;
	void *req = (void *)0; 
	void *result = (void *)0; 
	char buf[DATA_SIZE] = {0,};
    char res[DATA_SIZE] = {0,};

	shmid = shmget((key_t)1234, DATA_SIZE, 0666|IPC_CREAT); 
	shmid2 = shmget((key_t)1235, DATA_SIZE, 0666|IPC_CREAT); 
	if (shmid == -1) 
    { 
        perror("shmget failed : "); 
        exit(0); 
    } 

    req = shmat(shmid, (void *)0, 0); 
    result = shmat(shmid2, (void *)0, 0); 
    if (req == (void *)-1) 
    { 
        perror("shmat failed : "); 
        exit(0); 
    }
    while(1){
        memset(buf, 0, sizeof(buf));
    	scanf("%s", buf);
        getchar();
    	buf[strlen(buf)] = 0;
	    strcpy(req, buf);
        // printf("%s\n", req);
        sleep(1); // 1초 이하로 sleep하게 되면 데이터를 얻어오는데 오류가 난다.
        memcpy(res, result, strlen(result) + 1);
	    printf("%s\n", (char *) res);
    }

	
}