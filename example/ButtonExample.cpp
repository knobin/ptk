#include "ptk/Application.hpp"
#include "ptk/widgets/Button.hpp"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main(int argc, char* argv[])
{
    pTK::Application app("ButtonExample Application", argc, argv);
    pTK::Window window("ButtonExample Window", {SCR_WIDTH, SCR_HEIGHT});

    std::shared_ptr<pTK::Button> defaultBtn = std::make_shared<pTK::Button>(pTK::Button::Style::Default);
    defaultBtn->setText("Default Button");
    window.add(defaultBtn);
    defaultBtn->onClick([&defaultBtn](const pTK::ClickEvent&) {
        std::cout << defaultBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> successBtn = std::make_shared<pTK::Button>(pTK::Button::Style::Success);
    successBtn->setText("Success Button");
    window.add(successBtn);
    successBtn->onClick([&successBtn](const pTK::ClickEvent&) {
        std::cout << successBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> dangerBtn = std::make_shared<pTK::Button>(pTK::Button::Style::Danger);
    dangerBtn->setText("Danger Button");
    window.add(dangerBtn);
    dangerBtn->onClick([&dangerBtn](const pTK::ClickEvent&) {
        std::cout << dangerBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> customBtn = std::make_shared<pTK::Button>();
    customBtn->setText("Custom Button");
    customBtn->setColor(pTK::Color(0x808080FF));
    customBtn->setTextColor(pTK::Color(0xFFFFFFFF));
    customBtn->setCornerRadius(5);
    customBtn->setClickColor(pTK::Color(0x656565FF));
    customBtn->setHoverColor(pTK::Color(0x707070FF));
    window.add(customBtn);
    customBtn->onClick([&customBtn](const pTK::ClickEvent&) {
        std::cout << customBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> customStyleBtn = std::make_shared<pTK::Button>();
    pTK::Button::Style style = pTK::Button::Style::Default;
    style.color = pTK::Color(0x808080FF);
    style.hoverColor = pTK::Color(0x707070FF);
    style.clickColor = pTK::Color(0x656565FF);
    customStyleBtn->setStyle(style);
    customStyleBtn->setText("Custom Style Button");
    window.add(customStyleBtn);
    customStyleBtn->onClick([&customStyleBtn](const pTK::ClickEvent&) {
        std::cout << customStyleBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> customSizeBtn = std::make_shared<pTK::Button>(style);
    customSizeBtn->setSize(pTK::Size(250, 100));
    customSizeBtn->setText("Custom Size Button");
    window.add(customSizeBtn);
    customSizeBtn->onClick([&customSizeBtn](const pTK::ClickEvent&) {
        std::cout << customSizeBtn->getText() << " clicked!\n";
        return false;
    });

    std::shared_ptr<pTK::Button> customLabelSizeBtn = std::make_shared<pTK::Button>(style);
    customLabelSizeBtn->setFontSize(24);
    customLabelSizeBtn->setText("Custom Font Size Button");
    window.add(customLabelSizeBtn);
    customLabelSizeBtn->onClick([&customLabelSizeBtn](const pTK::ClickEvent&) {
        std::cout << customLabelSizeBtn->getText() << " clicked!\n";
        return false;
    });

    window.show();

    return app.exec(&window);
}
