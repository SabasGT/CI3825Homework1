//
//  main.c
//  sistemas
//
//  Created by Jhonaiker Blanco on 16/2/23.
//  Copyright © 2023 Jhonaiker Blanco. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define HASH_SIZE 20

int getHash(char text[20]){
    int counter = 0;
    
    for(int i = 0; i < strlen(text); i++){
        counter = counter + text[i];
    }
    return counter % 50;
}


int main(int argc, const char * argv[]) {

    typedef struct user {
        char username[20];
        char description[100];
        int password;
        char *tweets[5][280];
        struct user *usersFollowed[20];
        int amountOfUsersFollowed;
    } user;
    
    char action[10];
    char* newUsername[20];
    char* newPassword[20];
    char* description[100];
    char* username[20];
    char* password[20];
    int currentHashValue = 0;
    
    struct user usersInProgam[50][4];
    int amountOfUsersByHash[50];
    int amountOfUsersInCurrentHash = 0;
    
    int positionInHashOfUser = 0;
    
    int userTaken = 0;


    
    while(strcmp("leave", action) != 0){
        printf("DON’T MISS WHAT’S HAPPENING! LOGIN, SIGNUP OR LEAVE\n");
        strcpy(action, "");
        scanf("%s", action);
        
        if(strcmp("signup", action) == 0){
            
            printf("Username: ");
            scanf("%s", newUsername);
            
            printf("Password: ");
            scanf("%s", newPassword);
            
            printf("Description: ");
            scanf("%s", description);
            
            currentHashValue = getHash(newUsername);
            
            amountOfUsersInCurrentHash = amountOfUsersByHash[currentHashValue];
            
            userTaken = 0;
            
            for(int i = 0; i < amountOfUsersInCurrentHash; i++){
                if(strcmp(usersInProgam[amountOfUsersInCurrentHash][i].username, newUsername) == 0){
                    userTaken = 1;
                    break;
                }
            }
            
            if(userTaken == 1){
                printf("Username already taken");
            } else {
                strcpy(usersInProgam[currentHashValue][amountOfUsersInCurrentHash].username, newUsername);
                strcpy(usersInProgam[currentHashValue][amountOfUsersInCurrentHash].description, description);
                usersInProgam[currentHashValue][amountOfUsersInCurrentHash].password = getHash(newPassword);
                usersInProgam[currentHashValue][amountOfUsersInCurrentHash].amountOfUsersFollowed = 0;
                
                amountOfUsersByHash[currentHashValue] = amountOfUsersByHash[currentHashValue] + 1;
            }
            
        } else if(strcmp("login", action) == 0){
            
            printf("Username: ");
            scanf("%s", username);
            
            currentHashValue = getHash(username);
            amountOfUsersInCurrentHash = amountOfUsersByHash[currentHashValue];
            
            
            userTaken = 0;
            
            for(int i = 0; i < amountOfUsersInCurrentHash; i++){
 
                if(strcmp(usersInProgam[currentHashValue][i].username, username) == 0){
                    userTaken = 1;
                    positionInHashOfUser = i;
                    break;
                }
            }
            
            if(userTaken == 1){
                
                printf("Password: ");
                scanf("%s", password);
                
                if(usersInProgam[currentHashValue][positionInHashOfUser].password == getHash(password)){
                    printf("Login successfully \n");
                    char nextAction[10] = "";
                    char userToLogin[20] = "";
                    
                    int amountOfUsersInCurrentHash = 0;
                    
                    
                    while(strcmp("logout", nextAction) != 0){
                        printf("WHAT’S HAPPENING? \n");
                        scanf("%s", nextAction);
                        
                        if(strcmp("+", nextAction) == 0){
                            printf("You can write a new tweet \n");
                        } else if(strcmp("@", nextAction) == 0){
                            
                            
                            char userToCheck[20];
                            printf("Check a user: ");
                            scanf("%s", userToCheck);
                            
                            int currentHashValueToCheck = getHash(userToCheck);
                            int amountOfUsersInCurrentHashToCheck = amountOfUsersByHash[currentHashValueToCheck];
                            
                            int userExists = 0;
                            int positionInHashOfUser = 0;
                            
                            
                            for(int i = 0; i < amountOfUsersInCurrentHashToCheck; i++){
                                if(strcmp(usersInProgam[currentHashValueToCheck][i].username, userToCheck) == 0){
                                    userExists = 1;
                                    positionInHashOfUser = i;
                                    break;
                                }
                            }
                            if(userExists){
                                char actionToDo[20] = "";
                                int isUserFollowed = 0;
                                printf("The user exists! \n");
                                printf("It's description is: %s \n", usersInProgam[currentHashValueToCheck][positionInHashOfUser].description);
                                
                                for(int i = 0; i < usersInProgam[currentHashValue][positionInHashOfUser].amountOfUsersFollowed; i++){
                                    if(strcmp(userToCheck, usersInProgam[currentHashValue][positionInHashOfUser].usersFollowed[i]->username)){
                                        isUserFollowed = 1;
                                        break;
                                    }
                                }
                                
                                if(isUserFollowed == 1){
                                    printf("You already follow this user \n");
                                } else {
                                    char wantToLogin[10] = "";
                                    
                                    while(strcmp("no", wantToLogin) != 0 && strcmp("yes", wantToLogin) != 0){
                                        printf("Do you want to follow to this user? Write 'yes' or 'no' \n");
                                        scanf("%s", wantToLogin);
                                        
                                        if(!strcmp("yes", wantToLogin)){
                                            printf("Now you follow this user \n");
                                            int currentAmountOfUsersFollowed = usersInProgam[currentHashValue][positionInHashOfUser].amountOfUsersFollowed;
                                            
                                            usersInProgam[currentHashValue][positionInHashOfUser].usersFollowed[currentAmountOfUsersFollowed] = &usersInProgam[currentHashValueToCheck][amountOfUsersInCurrentHashToCheck];
                                            
                                            usersInProgam[currentHashValue][positionInHashOfUser].amountOfUsersFollowed++;
                                            
                                        } else if(!strcmp("no", wantToLogin)){
                                            printf("You don't want to follow this user \n");
                                        } else {
                                            printf("This command does not exist \n");
                                        }
                                    }
                                }
                            } else {
                                printf("This user does not exist \n");
                            }
                            
                            
                        } else if(strcmp("logout", nextAction) == 0){
                            printf("You logged out from your account \n");
                        } else {
                            printf("That command does not exist \n");
                        }
                    }
                } else {
                    printf("Wrong password \n");
                }
                
            } else {
                printf("There is not a user with that username \n");
            }
            
        } else if(strcmp("leave", action) == 0){
            printf("You left the app \n");
        } else {
           printf("Invalid action \n");
        }
    }

    return 0;
}