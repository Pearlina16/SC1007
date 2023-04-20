#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
 
    int index = hash(key);
    int value = index;
    int store;

    do{
        if(hashTable[index].indicator == EMPTY){
            if (hashTable[value].indicator==USED && hashTable[value].next==-1)
            {
                hashTable[value].next = index;
            }
            else if(hashTable[value].indicator==USED && hashTable[value].next != -1){
                store = value;
                while(hashTable[store].indicator==USED && hashTable[store].next!= -1){
                    store = hashTable[store].next;
                }
                hashTable[store].next = index;
            }
            hashTable[index].indicator=USED;
            hashTable[index].key = key;
            return index;
        }
        else if(hashTable[index].key==key && hashTable[index].indicator==USED)
            return -1;
        else if(hashTable[index].indicator==USED)
            index = (index+1)%TABLESIZE;

            
    }while (index!=value);

        return TABLESIZE+1;

    }

//     int value = hash(key);
//     int i = value;
//     int store, b;

//     do{
//         if(hashTable[i].indicator==EMPTY){
//             if(hashTable[value].indicator == USED && hashTable[value].next == -1){
//                 hashTable[value].next = i;
//             }
//             else if(hashTable[value].indicator == USED && hashTable[value].next!= -1){
//                 store = value;
//                 while(hashTable[store].indicator ==USED && hashTable[store].next != -1){
//                     store = hashTable[store].next;
//                 }
//                 hashTable[store].next = i;
//             }
//             hashTable[i].indicator = USED;
//             hashTable[i].key = key;

//             return i;
//         }
//         else if(hashTable[i].indicator ==USED && hashTable[i].key == key)
//             return -1;

//         else if(hashTable[i].indicator == USED)
//             i = (i+1)%TABLESIZE;
        
//     }while(i!=value);
    
//     return TABLESIZE+1;
// }


    // int value = hash(key);
    // int i = value;
    // int a,b;
 
    // int size = TABLESIZE;
    // do{
    //     if(hashTable[i].indicator==EMPTY){
    //         if(hashTable[value].indicator==USED && hashTable[value].next==-1) {
    //             hashTable[value].next = i;
    //         }
    //         else if(hashTable[value].indicator==USED && hashTable[value].next!=-1){
    //             a = value;
    //             while(hashTable[a].indicator==USED && hashTable[a].next!=-1){
    //                 a = hashTable[a].next;
    //             }
    //             hashTable[a].next = i;
    //         }
    //         hashTable[i].key = key;
    //         hashTable[i].indicator = USED;
            
    //         return i;
    //     }
    //     else if(hashTable[i].key == key)
    //         return -1;
    //     else{
    //         i = (i+1)%size;

    //     }
    // }while(i!=value);

    // return 100000;


int HashFind(int key, HashSlot hashTable[])
{
     // Write your code here
    int value = hash(key);
    int i = value;

    if(i!=-1){
        while(hashTable[i].key!=key && hashTable[i].indicator==USED)
        i = hashTable[i].next;
        
        if(hashTable[i].key == key)
        return i;
    }
    return -1;
}