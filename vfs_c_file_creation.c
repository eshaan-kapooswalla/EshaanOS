#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum to differentiate between file and directory
typedef enum {
    FILE_TYPE_FILE,
    FILE_TYPE_DIRECTORY
} FileType;

// Structure to represent a file or directory node
typedef struct FileNode {
    char* name;
    FileType type;
    char* content;
    struct FileNode* parent;
    struct FileNode** children;
    int childCount;
} FileNode;

// Function to create a new file node
FileNode* create_new_node(const char* name, FileType type) {
    FileNode* node = (FileNode*)malloc(sizeof(FileNode));
    node->name = strdup(name);
    node->type = type;
    node->content = NULL;
    node->parent = NULL;
    node->children = NULL;
    node->childCount = 0;
    return node;
}

// Function to create a new directory
FileNode* create_directory(FileNode* parent, const char* name) {
    for (int i = 0; i < parent->childCount; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            printf("Directory '%s' already exists\n", name);
            return NULL;
        }
    }
    FileNode* new_dir = create_new_node(name, FILE_TYPE_DIRECTORY);
    new_dir->parent = parent;
    parent->children = realloc(parent->children, sizeof(FileNode*) * (parent->childCount + 1));
    parent->children[parent->childCount++] = new_dir;
    printf("Directory '%s' created successfully\n", name);
    return new_dir;
}

// Function to create a new file
FileNode* create_file(FileNode* directory, const char* filename) {
    for (int i = 0; i < directory->childCount; i++) {
        if (strcmp(directory->children[i]->name, filename) == 0) {
            printf("File '%s' already exists\n", filename);
            return NULL;
        }
    }
    if (strlen(filename) == 0 || strchr(filename, '/')) {
        printf("Invalid filename '%s'\n", filename);
        return NULL;
    }
    FileNode* new_file = create_new_node(filename, FILE_TYPE_FILE);
    new_file->parent = directory;
    directory->children = realloc(directory->children, sizeof(FileNode*) * (directory->childCount + 1));
    directory->children[directory->childCount++] = new_file;
    printf("File '%s' created successfully\n", filename);
    return new_file;
}

// Function to list the contents of a directory
void list_contents(FileNode* directory) {
    printf("Contents of directory '%s':\n", directory->name);
    for (int i = 0; i < directory->childCount; i++) {
        if (directory->children[i]->type == FILE_TYPE_FILE) {
            printf("- File: %s\n", directory->children[i]->name);
        } else {
            printf("- Directory: %s\n", directory->children[i]->name);
        }
    }
}

// Function to free the entire file system
void delete_file_system(FileNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->childCount; i++) {
        delete_file_system(root->children[i]);
    }
    free(root->name);
    free(root->content);
    free(root->children);
    free(root);
}

int main() {
    // Create the root directory
    FileNode* root = create_new_node("root", FILE_TYPE_DIRECTORY);
    // Create a few directories
    create_directory(root, "docs");
    create_directory(root, "pics");
    // Create some files
    create_file(root, "notes.txt");
    create_file(root->children[0], "report.doc");
    create_file(root->children[1], "vacation.jpg");
    // List the contents of root directory
    list_contents(root);
    // Clean up
    delete_file_system(root);
    return 0;
} 