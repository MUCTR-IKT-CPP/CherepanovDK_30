#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <filesystem>
#include <regex>
#include <stdexcept>

class File {
public:
    std::string name;
    std::string description;
    
    File(std::string name, std::string description)
        : name(name), description(description) {}

    void rename(const std::string& new_name) {
        name = new_name;
    }
};

class Directory {
public:
    std::string name;
    Directory* parent;
    std::vector<std::shared_ptr<Directory>> subdirectories;
    std::vector<std::shared_ptr<File>> files;

    Directory(std::string name, Directory* parent = nullptr)
        : name(name), parent(parent) {}

    void create_file(const std::string& filename, const std::string& description) {
        files.push_back(std::make_shared<File>(filename, description));
    }

    void create_dir(const std::string& dir_name) {
        subdirectories.push_back(std::make_shared<Directory>(dir_name, this));
    }

    bool delete_object(const std::string& object_name) {
        // Find and remove file
        auto file_it = std::find_if(files.begin(), files.end(), [&object_name](const std::shared_ptr<File>& file) {
            return file->name == object_name;
        });

        if (file_it != files.end()) {
            files.erase(file_it);
            return true;
        }

        // Find and remove directory
        auto dir_it = std::find_if(subdirectories.begin(), subdirectories.end(), [&object_name](const std::shared_ptr<Directory>& dir) {
            return dir->name == object_name;
        });

        if (dir_it != subdirectories.end()) {
            if (dir_it->get()->subdirectories.empty() && dir_it->get()->files.empty()) {
                subdirectories.erase(dir_it);
                return true;
            } else {
                throw std::runtime_error("Error: Cannot delete directory with files or subdirectories!");
            }
        }

        return false;
    }

    void show_tree(int depth = 0) const {
        std::string indent(depth, ' ');
        std::cout << indent << name << "/" << std::endl;
        
        for (const auto& file : files) {
            std::cout << indent << "  " << file->name << std::endl;
        }

        for (const auto& subdir : subdirectories) {
            subdir->show_tree(depth + 2);
        }
    }

    std::shared_ptr<Directory> find_directory(const std::string& path) {
        if (path == ".." && parent != nullptr) {
            return parent->find_directory(path);  // go back to parent
        }

        for (const auto& subdir : subdirectories) {
            if (subdir->name == path) {
                return subdir;
            }
        }
        return nullptr;
    }
};

class FileSystem {
public:
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> current_directory;

    FileSystem(const std::string& root_name) {
        root = std::make_shared<Directory>(root_name);
        current_directory = root;
    }

    void change_directory(const std::string& dir_name) {
        if (dir_name == "..") {
            if (current_directory->parent != nullptr) {
                current_directory = std::shared_ptr<Directory>(current_directory->parent);
            } else {
                throw std::runtime_error("Error: Already at root directory!");
            }
        } else {
            auto subdir = current_directory->find_directory(dir_name);
            if (subdir) {
                current_directory = subdir;
            } else {
                throw std::runtime_error("Error: Directory not found!");
            }
        }
    }


    void create_dir(const std::string& name) {
        current_directory->create_dir(name);
    }

    void create_file(const std::string& name, const std::string& description) {
        current_directory->create_file(name, description);
    }

    void delete_object(const std::string& name) {
        if (!current_directory->delete_object(name)) {
            throw std::runtime_error("Error: Object not found!");
        }
    }

    void show_tree() const {
        current_directory->show_tree();
    }
};

void print_menu() {
    std::cout << "Available commands:\n"
              << "create_dir <name>  - Create directory\n"
              << "create_file <name> <description> - Create file\n"
              << "rename <old_name> <new_name> - Rename file or directory\n"
              << "delete <name> - Delete file or directory\n"
              << "move <name> <to> - Move file or directory\n"
              << "change_dir <name> - Change directory\n"
              << "show_tree - Show directory tree\n"
              << "exit - Exit the program\n";
}

int main() {
    FileSystem fs("root");
    std::string command;

    while (true) {
        print_menu();
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        try {
            if (command.rfind("create_dir ", 0) == 0) {
                std::string name = command.substr(11);
                fs.create_dir(name);
            } else if (command.rfind("create_file ", 0) == 0) {
                size_t space_pos = command.find(' ', 12);
                std::string name = command.substr(12, space_pos - 12);
                std::string description = command.substr(space_pos + 1);
                fs.create_file(name, description);
            } else if (command.rfind("rename ", 0) == 0) {
                size_t space_pos = command.find(' ', 7);
                std::string old_name = command.substr(7, space_pos - 7);
                std::string new_name = command.substr(space_pos + 1);
                // This part can be expanded for renaming files or directories
            } else if (command.rfind("delete ", 0) == 0) {
                std::string name = command.substr(7);
                fs.delete_object(name);
            } else if (command.rfind("move ", 0) == 0) {
                // Implement move functionality here
            } else if (command.rfind("change_dir ", 0) == 0) {
                std::string name = command.substr(11);
                fs.change_directory(name);
            } else if (command == "show_tree") {
                fs.show_tree();
            } else if (command == "exit") {
                break;
            } else {
                std::cerr << "Unknown command!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
