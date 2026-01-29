#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "SimpleLabel.h"
#include "RichLabel.h"
#include "CustomLabel.h"
#include "HelpLabel.h"
#include "SimpleHelpProvider.h"
#include "LabelDecorator.h"
#include "RandomTransformDecorator.h"
#include "CyclingTransformDecorator.h"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "RightTrimTransformation.h"
#include "NormalizeSpaceTransformation.h"
#include "DecorateTransformation.h"
#include "CensorFactory.h"
#include "ReplaceTransformation.h"

// Helper to build a list of transformations for Advanced Decorators
std::vector<std::shared_ptr<TextTransformation>> buildTransformList() {
    std::vector<std::shared_ptr<TextTransformation>> list;
    int choice = -1;

    while (true) {
        std::cout << "\033[2J\033[H";
        std::cout << "\n--- Build Transformation Pool (0 to finish) ---" << std::endl;
        std::cout << "1. Capitalize    2. Decorate    3. Normalize" << std::endl;
        std::cout << "4. Left Trim     5. Right Trim   6. Censor (Flyweight)" << std::endl;
        std::cout << "Current Pool Size: " << list.size() << "\nSelection: ";

        if (!(std::cin >> choice) || choice == 0) break;
        std::cin.ignore();

        switch (choice) {
        case 1:
            list.push_back(std::make_shared<CapitalizeTransformation>());
            break;
        case 2:
            list.push_back(std::make_shared<DecorateTransformation>());
            break;
        case 3:
            list.push_back(std::make_shared<NormalizeSpaceTransformation>());
            break;
        case 4:
            list.push_back(std::make_shared<LeftTrimTransformation>());
            break;
        case 5:
            list.push_back(std::make_shared<RightTrimTransformation>());
            break;
        case 6: {
            std::cout << "Word to censor: ";
            std::string w;
            std::getline(std::cin, w);
            list.push_back(CensorFactory::getCensor(w));
            break;
        }
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
    std::cout << "\033[2J\033[H";
    return list;
}

std::string colourToString(Colour col) {
    switch (col) {
    case Colour::Red:   
        return "Red";
    case Colour::Green: 
        return "Green";
    case Colour::Blue:  
        return "Blue";
    case Colour::White: 
        return "White";
    case Colour::Black: 
        return "Black";
    default:            
        return "Unknown";
    }
}

void printMenu() {
    std::cout << "\n======================== Label Menu ========================" << std::endl;
    std::cout << "1.  New Simple Label                 2. New Rich Label" << std::endl;
    std::cout << "3.  New Custom Label (Lazy Loading)" << std::endl;
    std::cout << "-------------------- Single Transformations ----------------" << std::endl;
    std::cout << "4.  Add Capitalize                   5. Add Decorate" << std::endl;
    std::cout << "6.  Add Left Trim                    7. Add Right Trim" << std::endl;
    std::cout << "8.  Add Normalize Space              9. Add Replace (A -> B)" << std::endl;
    std::cout << "10. Add Censor                       11. Add Help Text" << std::endl;
    std::cout << "-------------------- Advanced Decorators -------------------" << std::endl;
    std::cout << "15. Add RANDOM Decorator             16. Add CYCLING Decorator" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "12. View Result (getText)            13. View Metadata" << std::endl;
    std::cout << "14. UNDO Last Decorator              0. Exit" << std::endl;
    std::cout << "Selection: ";
}

int main() {
    std::shared_ptr<Label> currentLabel = nullptr;
    int choice = -1;

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;
        std::cout << "\033[2J\033[H";
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::cout << "Text: ";
            std::string t; std::getline(std::cin, t);
            currentLabel = std::make_shared<SimpleLabel>(t);
            break;
        }
        case 2: {
            std::cout << "Text: ";
            std::string t; std::getline(std::cin, t);

            std::cout << "Choose Colour (1: Red, 2: Green, 3: Blue, 4: White, 5: Black): ";
            int colorPick;
            std::cin >> colorPick;
            Colour col = Colour::Black;
            if (colorPick == 1) 
                col = Colour::Red;
            else if (colorPick == 2) 
                col = Colour::Green;
            else if (colorPick == 3) 
                col = Colour::Blue;
            else if (colorPick == 4) 
                col = Colour::White;

            std::cout << "Choose Font (1: Arial, 2: Verdana, 3: Times New Roman, 4: Consolas): ";
            int fontPick;
            std::cin >> fontPick;
            std::string fontName = "Arial";
            if (fontPick == 2) 
                fontName = "Verdana";
            else if (fontPick == 3) 
                fontName = "Times New Roman";
            else if (fontPick == 4) 
                fontName = "Consolas";

            unsigned int fontSize = 12;
            do {
                std::cout << "Enter Font Size (8-72): ";
                std::cin >> fontSize;
                if (fontSize < 8 || fontSize > 72) {
                    std::cout << "Invalid size. Please stay between 8 and 72.\n";
                }
            } while (fontSize < 8 || fontSize > 72);

            currentLabel = std::make_shared<RichLabel>(t, col, fontName, fontSize);
            std::cout << "Rich Label created successfully.\n";
            break;
        }
        case 3: {
            std::cout << "Access Timeout: ";
            int timeout; std::cin >> timeout;
            currentLabel = std::make_shared<CustomLabel>(timeout);
            break;
        }
        case 4: {
            if (currentLabel) {
                currentLabel = LabelDecorator::create(
                    currentLabel,
                    std::make_shared<CapitalizeTransformation>()
                );
            }
            break;
        }
        case 5: {
            if (currentLabel) {
                currentLabel = LabelDecorator::create(
                    currentLabel,
                    std::make_shared<DecorateTransformation>()
                );
            }
            break;
        }
        case 6: {
            if (currentLabel) {
                currentLabel = LabelDecorator::create(
                    currentLabel,
                    std::make_shared<LeftTrimTransformation>()
                );
            }
            break;
        }
        case 7: {
            if (currentLabel) {
                currentLabel = LabelDecorator::create(
                    currentLabel,
                    std::make_shared<RightTrimTransformation>()
                );
            }
            break;
        }
        case 8: {
            if (currentLabel) {
                currentLabel = LabelDecorator::create(
                    currentLabel,
                    std::make_shared<NormalizeSpaceTransformation>()
                );
            }
            break;
        }
        case 9: {
            if (!currentLabel) break;
            std::cout << "From: "; 
            std::string f; 
            std::getline(std::cin, f);
            std::cout << "To: ";   
            std::string t; 
            std::getline(std::cin, t);
            currentLabel = LabelDecorator::create(currentLabel, std::make_shared<ReplaceTransformation>(f, t));
            break;
        }
        case 10: {
            if (!currentLabel) break;
            std::cout << "Word to censor: ";
            std::string w; 
            std::getline(std::cin, w);
            currentLabel = LabelDecorator::create(currentLabel, CensorFactory::getCensor(w));
            break;
        }
        case 11: {
            if (!currentLabel) break;
            std::cout << "Help string: ";
            std::string h; 
            std::getline(std::cin, h);
            currentLabel = HelpLabel::create(currentLabel, std::make_shared<SimpleHelpProvider>(h));
            break;
        }
        case 12:
            if (currentLabel) 
                std::cout << "\nOutput: \"" << currentLabel->getText() << "\"\n";
            else 
                std::cout << "Create a label first!\n";
            break;
        case 13: {
            if (!currentLabel) 
                break;
            auto help = std::dynamic_pointer_cast<HelpLabel>(currentLabel);
            if (help) 
                std::cout << "Help: " << help->getHelpText() << "\n";
            auto rich = std::dynamic_pointer_cast<RichLabelProperties>(currentLabel);
            if (rich) {
                std::cout << "Rich Metadata:" << std::endl;
                std::cout << "  - Colour: " << colourToString(rich->getColour()) << std::endl;
                std::cout << "  - Font:   " << rich->getFontName() << std::endl;
                std::cout << "  - Size:   " << rich->getFontSize() << "pt" << std::endl;
            }
            else {
                std::cout << "No rich properties found.\n";
            }
            break;
        }
        case 14: {
            if (!currentLabel) 
                break;
            auto decorator = std::dynamic_pointer_cast<LabelDecorator>(currentLabel);
            if (decorator) {
                currentLabel = LabelDecorator::remove(currentLabel, decorator);
                std::cout << "Last decorator removed.\n";
            }
            else 
                std::cout << "No decorators to remove.\n";
            break;
        }
        case 15: {
            if (!currentLabel) 
                break;
            auto list = buildTransformList();
            if (!list.empty()) 
                currentLabel = std::make_shared<RandomTransformDecorator>(currentLabel, list);
            break;
        }
        case 16: {
            if (!currentLabel) 
                break;
            auto list = buildTransformList();
            if (!list.empty()) 
                currentLabel = std::make_shared<CyclingTransformDecorator>(currentLabel, list);
            break;
        }
        default: 
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}