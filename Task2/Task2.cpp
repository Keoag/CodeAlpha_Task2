#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void list_files(const std::string& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path))
            std::cout << entry.path().filename() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Error listing files: " << e.what() << '\n';
    }
}

void view_file(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::cout << "File content of " << filename << ":\n";
            std::string line;
            while (getline(file, line)) {
                std::cout << line << '\n';
            }
            file.close();
        }
        else {
            std::cout << "Unable to open file " << filename << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error viewing file: " << e.what() << '\n';
    }
}

void create_directory(const std::string& dirname) {
    try {
        if (fs::create_directory(dirname))
            std::cout << "Directory created successfully.\n";
        else
            std::cout << "Failed to create directory.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << '\n';
    }
}

void copy_file(const std::string& source, const std::string& destination) {
    try {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error copying file: " << e.what() << '\n';
    }
}

void move_file(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error moving file: " << e.what() << '\n';
    }
}

void navigate_directory(std::string& current_path) {
    std::string new_directory;
    std::cout << "Enter the directory name: ";
    std::cin >> new_directory;

    fs::path new_path = current_path;
    new_path /= new_directory;

    if (fs::exists(new_path) && fs::is_directory(new_path)) {
        current_path = new_path.string();
        std::cout << "Navigated to: " << current_path << '\n';
    }
    else {
        std::cout << "Invalid directory.\n";
    }
}

int main() {
    std::string current_path = fs::current_path().string();
    int choice;

    do {
        clear_screen();
        std::cout << "Current directory: " << current_path << "\n\n";
        std::cout << "File Manager Menu:\n";
        std::cout << "1. List files and directories\n";
        std::cout << "2. View file content\n";
        std::cout << "3. Create directory\n";
        std::cout << "4. Copy file\n";
        std::cout << "5. Move file\n";
        std::cout << "6. Navigate to subdirectory\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            list_files(current_path);
            break;
        case 2: {
            std::string filename;
            std::cout << "Enter the file name: ";
            std::cin >> filename;
            view_file(current_path + "/" + filename);
            break;
        }
        case 3: {
            std::string dirname;
            std::cout << "Enter the directory name: ";
            std::cin >> dirname;
            create_directory(current_path + "/" + dirname);
            break;
        }
        case 4: {
            std::string source, destination;
            std::cout << "Enter source file name: ";
            std::cin >> source;
            std::cout << "Enter destination file name: ";
            std::cin >> destination;
            copy_file(current_path + "/" + source, current_path + "/" + destination);
            break;
        }
        case 5: {
            std::string source, destination;
            std::cout << "Enter source file name: ";
            std::cin >> source;
            std::cout << "Enter destination file name: ";
            std::cin >> destination;
            move_file(current_path + "/" + source, current_path + "/" + destination);
            break;
        }
        case 6:
            navigate_directory(current_path);
            break;
        case 7:
            std::cout << "Exiting the file manager.\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    } while (choice != 7);

    return 0;
}
