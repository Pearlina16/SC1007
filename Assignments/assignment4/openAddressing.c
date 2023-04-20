#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int i;
   int count=0;
   int num;
   int deleted=-1;
  
 
    for(int j=0; j<TABLESIZE; j++){ 
        i = (hash1(key) + j*hash2(key)) % TABLESIZE; 
 
        if(hashTable[i].indicator == EMPTY){ 
            if(deleted == -1){ 
                hashTable[i].key = key; 
                hashTable[i].indicator = USED; 
                return count; 
            } 
 
            else{ 
                hashTable[num].key = key; 
                hashTable[num].indicator = USED; 
                return count; 
            } 
        } 

        else if(hashTable[i].indicator == USED){ 

            if(hashTable[i].key == key) 
                return -1; 
 
            else 
                count++; 
        } 

        else if(hashTable[i].indicator == DELETED && deleted == -1){ 
            num = i; 
            deleted = 1; 
        } 
    } 
    if(deleted == -1) 
        return count; 
 
    else{ 
        hashTable[num].key = key; 
        hashTable[num].indicator = USED; 
        return count; 
    } 
   //Write your code here
//   int comparison=0;
//   int i = hash1(key);
//   int j = hash2(key);
//   int deleted = -1;
//   int count =0;

//     while(hashTable[i].indicator!= EMPTY){
//         if(hashTable[i].key == key && hashTable[i].indicator==USED)
//             return -1;
//         else if(hashTable[i].indicator == DELETED){
//             deleted = i;
//         }
//         else{
//             count++;
//         }
//         i = (i + j) % TABLESIZE;
//         comparison ++;

//         if(count>TABLESIZE){
//             if(deleted!= -1)
//             break;
//             else
//             return count;
//         }

//         while(i>TABLESIZE-1)
//         i = i - TABLESIZE;
//     } 
   

//     if(deleted!= -1){
//         hashTable[deleted].key = key;
//         hashTable[deleted].indicator = USED;
//     }
//     else{
//     hashTable[i].key = key;
//     hashTable[i].indicator = USED;
//     }
//     return comparison;

}
//     int comparison = 0;
//     int i;
//     int j;
//     int firstDeletedIndex = -1;

//     while (hashTable[i].indicator == USED)
//     {
//         if (hashTable[i].key == key)
//             return -1;

//         if (hashTable[i].indicator == DELETED && firstDeletedIndex == -1)
//             firstDeletedIndex = i;

//         i = (i + j) % TABLESIZE;
//         comparison++;

//         if (comparison > TABLESIZE)
//             return TABLESIZE;
//     }

//     if (hashTable[i].indicator == DELETED)
//         hashTable[i].key = key;
//     else if (firstDeletedIndex != -1)
//     {
//         hashTable[firstDeletedIndex].key = key;
//         hashTable[firstDeletedIndex].indicator = USED;
//     }
//     else
//     {
//         hashTable[i].key = key;
//         hashTable[i].indicator = USED;
//     }

//     return comparison;

    // int comparison= 0;
    // int i;
    // int firstdeleted= -1;
    // int count= 0;
    // int j;

    // for(j=0; j< TABLESIZE; j++){
    //     i = hash1(key +count *hash2(key));
    //     if(hashTable[i].indicator == USED && hashTable[i].key == key)
    //         return -1;
    //     else if(hashTable[i].indicator == USED){
    //         comparison++;
    //     }
    //     else if(hashTable[i].indicator == DELETED)
    //         firstdeleted = i;
    //     else if(hashTable[i].indicator == EMPTY)
    //         break;
        
    //     count++;
    // }
    // if (count >= (TABLESIZE-1))
    //     return TABLESIZE;

    // if(firstdeleted!= -1){
    //     hashTable[firstdeleted].key = key;
    //     hashTable[firstdeleted].indicator= USED;
    // }
    // else{
    //     hashTable[i].key = key;
    //     hashTable[i].indicator = USED;
    // }
    // return comparison;


int HashDelete(int key, HashSlot hashTable[])
{
   //Write your code here
    int i;
    int count =1;
 
   for(int j=0; j<TABLESIZE; j++){ 
        i = (hash1(key) + j*hash2(key)) % TABLESIZE; 
 
        if(hashTable[i].indicator == USED && hashTable[i].key == key){ 
                hashTable[i].indicator = DELETED; 
                return count; 
            } 

        else if(hashTable[i].indicator == DELETED && hashTable[i].key == key) 
            return -1; 
 
        else 
            count++; 
    } 
    return -1; 
    // int i = hash1(key);
    // int j = hash2(key);
    // int comparison=1;

    // for(int k =0; k<TABLESIZE; k++){
    //     if(hashTable[i].indicator==EMPTY)
    //         continue;
    //     if(hashTable[i].indicator==DELETED)
    //         continue;
    //     if(hashTable[i].indicator == USED && hashTable[i].indicator == key){
    //         hashTable[i].indicator = DELETED;
    //         return ++comparison;
    //     }
        
    //     i = (i+j)%TABLESIZE;
    // }
    //     return -1;

    // while(hashTable[i].indicator==USED){
    //     if(hashTable[i].key==key){
    //         hashTable[i].indicator=DELETED;
    //         return comparison;
    //     }

    //     i = (i+j)%TABLESIZE;
    //     comparison++;

    //     if(comparison>TABLESIZE)
    //     return -1;

    // }
    // return -1;

}