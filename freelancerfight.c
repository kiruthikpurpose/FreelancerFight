#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_PROJECTS 100
#define MAX_FREELANCERS 50
#define MAX_CLIENTS 50
#define MAX_BIDS 100

// Struct definitions
typedef struct {
    int projectId;
    char projectName[50];
    char projectDescription[100];
    float budget;
    int clientId;
    int freelancerId;
    int isAssigned;
} Project;

typedef struct {
    int freelancerId;
    char name[50];
    char skills[100];
    float rating;
} Freelancer;

typedef struct {
    int clientId;
    char name[50];
    char company[50];
} Client;

typedef struct {
    int bidId;
    int projectId;
    int freelancerId;
    float amount;
} Bid;

// Function prototypes
void postProject(Client *client, char *projectName, char *projectDescription, float budget);
void displayProjects(Project *projects, int numProjects);
void placeBid(Project *project, Freelancer *freelancer, float amount);
void manageContracts(Project *projects, Freelancer *freelancers, int numProjects, int numFreelancers);

// Global variables
Project projects[MAX_PROJECTS];
Freelancer freelancers[MAX_FREELANCERS];
Client clients[MAX_CLIENTS];
Bid bids[MAX_BIDS];
int numProjects = 0;
int numFreelancers = 0;
int numClients = 0;
int numBids = 0;

int main() {
    // Example usage
    Client client1 = { 1, "Alice", "Tech Solutions Inc." };
    clients[numClients++] = client1;

    Freelancer freelancer1 = { 1, "Bob", "Web Development, Python", 4.5 };
    freelancers[numFreelancers++] = freelancer1;

    postProject(&client1, "Website Development", "Build a responsive website for e-commerce", 1500.0);

    placeBid(&projects[0], &freelancer1, 1200.0);

    manageContracts(projects, freelancers, numProjects, numFreelancers);

    return 0;
}

// Function definitions

void postProject(Client *client, char *projectName, char *projectDescription, float budget) {
    Project newProject;
    newProject.projectId = numProjects + 1;
    strcpy(newProject.projectName, projectName);
    strcpy(newProject.projectDescription, projectDescription);
    newProject.budget = budget;
    newProject.clientId = client->clientId;
    newProject.isAssigned = 0;
    projects[numProjects++] = newProject;

    printf("Project '%s' posted successfully by %s from %s with a budget of $%.2f.\n",
           projectName, client->name, client->company, budget);
}

void displayProjects(Project *projects, int numProjects) {
    printf("\nAvailable Projects:\n");
    for (int i = 0; i < numProjects; ++i) {
        printf("Project ID: %d\n", projects[i].projectId);
        printf("Name: %s\n", projects[i].projectName);
        printf("Description: %s\n", projects[i].projectDescription);
        printf("Budget: $%.2f\n", projects[i].budget);
        printf("Client: %s\n", clients[projects[i].clientId - 1].name); // Client ID - 1 for index
        if (projects[i].isAssigned) {
            printf("Assigned to Freelancer ID %d\n", projects[i].freelancerId);
        } else {
            printf("Status: Open for Bids\n");
        }
        printf("\n");
    }
}

void placeBid(Project *project, Freelancer *freelancer, float amount) {
    Bid newBid;
    newBid.bidId = numBids + 1;
    newBid.projectId = project->projectId;
    newBid.freelancerId = freelancer->freelancerId;
    newBid.amount = amount;
    bids[numBids++] = newBid;

    printf("Freelancer %s has placed a bid of $%.2f for project '%s'.\n",
           freelancer->name, amount, project->projectName);
}

void manageContracts(Project *projects, Freelancer *freelancers, int numProjects, int numFreelancers) {
    printf("\nManaging Contracts:\n");
    for (int i = 0; i < numProjects; ++i) {
        if (!projects[i].isAssigned) {
            // Find the highest bid for the project
            float maxBid = 0.0;
            int maxBidderId = -1;
            for (int j = 0; j < numBids; ++j) {
                if (bids[j].projectId == projects[i].projectId && bids[j].amount > maxBid) {
                    maxBid = bids[j].amount;
                    maxBidderId = bids[j].freelancerId;
                }
            }
            if (maxBidderId != -1) {
                // Assign project to the freelancer with the highest bid
                projects[i].freelancerId = maxBidderId;
                projects[i].isAssigned = 1;
                printf("Project '%s' assigned to Freelancer ID %d.\n", projects[i].projectName, maxBidderId);
            } else {
                printf("No bids found for project '%s'.\n", projects[i].projectName);
            }
        }
    }
}
