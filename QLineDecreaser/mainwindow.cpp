#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ordering machine");

    ui->stackedWidget->setCurrentIndex(1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));
    timer->start(1000);

    QPixmap main_logo(":/images/logo_icon.png");
    ui->label_logo->setPixmap(main_logo.scaled(500, 300, Qt::KeepAspectRatio));

    QPixmap popcorn_pic(":/images/popcorn_logo.png");
    ui->popcorn_logo->setPixmap(popcorn_pic.scaled(320, 320, Qt::KeepAspectRatio));

    QPixmap nachos_pic(":/images/nachos_logo.png");
    ui->nachos_logo->setPixmap(nachos_pic.scaled(280, 280, Qt::KeepAspectRatio));

    QPixmap menu_pic(":/images/menu_logo.png");
    ui->label_menu->setPixmap(menu_pic.scaled(220, 220, Qt::KeepAspectRatio));

    QPixmap left_popcorn(":/images/left_popcorn.png");
    ui->leftPopcorn->setPixmap(left_popcorn.scaled(220, 220, Qt::KeepAspectRatio));

    QPixmap right_popcorn(":/images/right_popcorn.png");
    ui->rightPopcorn->setPixmap(right_popcorn.scaled(200, 200, Qt::KeepAspectRatio));

    QPixmap smile_pic(":/images/smile.png");
    ui->smilePic->setPixmap(smile_pic.scaled(60, 60, Qt::KeepAspectRatio));

    QPixmap thumb_pic(":/images/thumbup.png");
    ui->thumbPic->setPixmap(thumb_pic.scaled(60, 60, Qt::KeepAspectRatio));
}

struct itemPrice
{
    string itemName;
    double itemPrice;
};

//Globális csoda következik.
double totalPrice = 0;
string formattedTotalPrice = to_string(totalPrice);

vector<itemPrice> v;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");
    ui->label_date_time->setText(time_text);
}

void MainWindow::on_actionMain_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_actionProducts_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_actionCart_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_actionPay_triggered()
{
    if (v.empty()) {
        QMessageBox::warning(this, "Empty cart.", "Order cannot be done. The cart is empty.");
    } else {
    ui->stackedWidget->setCurrentIndex(3);
    }
}


void MainWindow::on_actionFeedback_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

string onClickedItem(string name, double price, bool hasShortName) {
    itemPrice ip;
    ip.itemName = name;
    ip.itemPrice = price;

    v.push_back(ip);
    totalPrice += ip.itemPrice;

    string str;

    if (hasShortName) {
    str = ip.itemName + "\t\t   $" + to_string(ip.itemPrice);
    } else {
    str = ip.itemName + "\t   $" + to_string(ip.itemPrice);
    }

    // Eltávolítjuk a sztring végén lévő nullákat
    size_t found = str.find_last_not_of('0');
    if (found != string::npos) {
        str = str.substr(0, found + 1);
    } else {
        // Az összes karakter nulla volt, tehát csak az ár marad
        str = str.substr(0, str.find('.') + 2);
    }
    formattedTotalPrice = to_string(totalPrice);
    size_t decimalPos = formattedTotalPrice.find('.');
    if (decimalPos != string::npos) {
        formattedTotalPrice = "$" + formattedTotalPrice.substr(0, decimalPos + 3) + " ";
    }
    return str;
}

void MainWindow::on_popcorn_clicked()
{
    string str = onClickedItem("Popcorn", 4.5, true);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}

void MainWindow::on_nachos_clicked()
{
    string str = onClickedItem("Nachos", 4.5, true);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}


void MainWindow::on_coke_clicked()
{
    string str = onClickedItem("Coke", 1.6, true);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}


void MainWindow::on_zeroCoke_clicked()
{
    string str = onClickedItem("Zero Coke", 1.6, true);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}


void MainWindow::on_popcornMenu_clicked()
{
    string str = onClickedItem("Popcorn menu", 5.8, false);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}


void MainWindow::on_nachosMenu_clicked()
{
    string str = onClickedItem("Nachos menu", 5.8, false);
    ui->itemsInCartList->addItem(str.c_str());
    // Beállítsd a totalPrice értékét a UI elemre
    ui->totalPriceInCart->setText(formattedTotalPrice.c_str());
    ui->labelPayPrice->setText(formattedTotalPrice.c_str());
}

void MainWindow::on_viewCartItems_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


// Back button
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


// Pay button
void MainWindow::on_pushButton_3_clicked()
{
    if (v.empty()) {
        QMessageBox::warning(this, "Empty cart.", "Order cannot be done. The cart is empty.");
    } else {
    ui->stackedWidget->setCurrentIndex(3);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_4_clicked()
{
    if (!v.empty()) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Remove items from cart.", "Are you sure want to delete all items from cart?", QMessageBox::No | QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        v.clear();
        ui->itemsInCartList->clear();
        totalPrice = 0;
        ui->totalPriceInCart->setText("$0.00 ");
        ui->labelPayPrice->setText("$0.00");
    } else {
        ui->stackedWidget->setCurrentIndex(0);
    }
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

struct receiptInfo {
    int receiptNum;
    QString customerName, orderNum;
};

void MainWindow::on_pushButton_5_clicked()
{
    // Ha nincs termék a kosrában => Ide kellene egy felugrő ablak.
    if (ui->textEditNum->text().isEmpty() && ui->checkTakeOrder->isChecked() == false) {
        QMessageBox::warning(this, "No order mode selected.", "Please, mark the way you want to get the order. :)");
    } else if (ui->textEditNum->text().isEmpty() == false && ui->checkTakeOrder->isChecked() == true){
        QMessageBox::warning(this, "Both order mode selected.", "Please, choose one way of getting the order. :)");
    } else {


    if (ui->textEditName->text().isEmpty()) {
         ui->textEditName->setText("Anonym");
    }

    ofstream outputFile;
    QString filePath;

    receiptInfo ri;
    ri.receiptNum = rand()%(1000000000 - 1000000 + 1) + 1000000;
    ri.customerName = ui->textEditName->text();
    ri.orderNum = ui->textEditNum->text();

    QString appDir = QCoreApplication::applicationDirPath();
    int lastSlashPos = appDir.lastIndexOf('/');

    // Ellenőrzi, hogy talál-e perjelet.
    if (lastSlashPos != -1) {
        // Kivágjuk a sztringet az utolsó perjel előtti részből.
        QString firstHalf = appDir.left(lastSlashPos);
        QString secondHalf = "/QLineDecreaser/SalesData.txt";


    // Megtekintjük a két értéket.
    qDebug() << "Az elérési útvonal első fele: " << firstHalf;
    qDebug() << "A elérési útvonal második fele: " << secondHalf;

    // Összetesszük az elérési útvonalat a két értékből.
    filePath = firstHalf + secondHalf;
    }

    // Fájl létrehozása/megnyitása.
    outputFile.open(filePath.toStdString(), ios::app);

    // Fájlba írás.
    if (outputFile) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        outputFile << "Receipt number: " << ri.receiptNum << endl;
        outputFile << "Customer name: " << ri.customerName.toStdString() << endl;
        if (ui->textEditNum->text().isEmpty()) {
        outputFile << "Order number: not selected" << endl;
        } else {
        outputFile << "Order number: " << ri.orderNum.toStdString() << endl;
        }
        outputFile << "Timestamp: " << formattedDateTime.toStdString() << endl;
        outputFile << "----------------------" << endl;
        outputFile << "Items \t\t Price" << endl;
        for (unsigned i = 0; i < v.size(); i++) {
            // A sok if-else ág a kimeneti fájl kimért elrendezése miatt volt szükséges, pusztán esztétikai okokból.
            if (v[i].itemName == "Popcorn") {
            outputFile << v[i].itemName << "\t\t  $" << v[i].itemPrice << endl;
            } else if (v[i].itemName == "Nachos") {
            outputFile << v[i].itemName << "\t\t  $" << v[i].itemPrice << endl;
            } else if (v[i].itemName == "Coke") {
            outputFile << v[i].itemName << "\t\t $" << v[i].itemPrice << endl;
            } else if (v[i].itemName == "Zero Coke") {
            outputFile << v[i].itemName << " \t  $" << v[i].itemPrice << endl;
            } else if (v[i].itemName == "Popcorn menu") {
            outputFile << v[i].itemName << " \t  $" << v[i].itemPrice << endl;
            } else if (v[i].itemName == "Nachos menu") {
            outputFile << v[i].itemName << " \t  $" << v[i].itemPrice << endl;
            }
        }
        outputFile << "----------------------" << endl;
        outputFile << "Total: \t\t $" << totalPrice << endl;
        outputFile << "\n\n-------------------- END OF RECEIPT --------------------\n\n\n";
      }
    // Fájl bezárása!
    outputFile.close();
    // Töröljük a munkamenetet.
    v.clear();
    totalPrice = 0;
    ui->itemsInCartList->clear();
    ui->textEditName->clear();
    ui->textEditNum->clear();
    ui->totalPriceInCart->setText("$0.00 ");
    ui->labelPayPrice->setText("$0.00");

    ui->stackedWidget->setCurrentIndex(6);
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Canceling order.", "Are you sure want to cancel the whole order?", QMessageBox::No | QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        v.clear();
        totalPrice = 0;
        ui->itemsInCartList->clear();
        ui->textEditName->clear();
        ui->textEditNum->clear();
        ui->totalPriceInCart->setText("$0.00 ");
        ui->labelPayPrice->setText("$0.00");
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->stackedWidget->setCurrentIndex(3);
    }
}


void MainWindow::on_pushBackToMain_clicked()
{
    resetRadioButtons();
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushBackToMain_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushBackToMain_2_clicked()
{
    ofstream outputFileFB;
    QString filePathFB;
    QString appDir = QCoreApplication::applicationDirPath();
    int lastSlashPos = appDir.lastIndexOf('/');

    // Ellenőrzi, hogy talál-e perjelet.
    if (lastSlashPos != -1) {
        // Kivágjuk a sztringet az utolsó perjel előtti részből.
        QString firstHalf = appDir.left(lastSlashPos);
        QString secondHalf = "/QLineDecreaser/FeedBackData.txt";
        filePathFB = firstHalf + secondHalf;
    }

    // Fájl létrehozása/megnyitása.
    outputFileFB.open(filePathFB.toStdString(), ios::app);

    // Ezzel a változóval nézzük meg, hogy volt-e bármi bejelölve.
    bool isSelected = false;

    if (true) {
    if (ui->tasteVeryLow->isChecked()) {
        isSelected = true;
    } else if (ui->tasteLow->isChecked()) {
        isSelected = true;
    } else if (ui->tasteMedium->isChecked()) {
        isSelected = true;
    } else if (ui->tasteLow->isChecked()) {
        isSelected = true;
    } else if (ui->tasteLow->isChecked()) {
        isSelected = true;
    }
    // Staff.
    if (ui->staffVeryLow->isChecked()) {
        isSelected = true;
    } else if (ui->staffLow->isChecked()) {
        isSelected = true;
    } else if (ui->staffMedium->isChecked()) {
        isSelected = true;
    } else if (ui->staffHigh->isChecked()) {
        isSelected = true;
    } else if (ui->staffVeryHigh->isChecked()) {
        isSelected = true;
    }
    // Temperature of food.
    if (ui->tempVeryLow->isChecked()) {
        isSelected = true;
    } else if (ui->tempLow->isChecked()) {
        isSelected = true;
    } else if (ui->tempMedium->isChecked()) {
        isSelected = true;
    } else if (ui->tempHigh->isChecked()) {
        isSelected = true;
    } else if (ui->tempVeryHigh->isChecked()) {
        isSelected = true;
    }
    // Decoration.
    if (ui->decorVeryLow->isChecked()) {
        isSelected = true;
    } else if (ui->decorLow->isChecked()) {
        isSelected = true;
    } else if (ui->decorMedium->isChecked()) {
        isSelected = true;
    } else if (ui->decorHigh->isChecked()) {
        isSelected = true;
    } else if (ui->decorVeryHigh->isChecked()) {
        isSelected = true;
    }
    // Cleaniness.
    if (ui->cleanVeryLow->isChecked()) {
        isSelected = true;
    } else if (ui->cleanLow->isChecked()) {
        isSelected = true;
    } else if (ui->cleanMedium->isChecked()) {
        isSelected = true;
    } else if (ui->cleanHigh->isChecked()) {
        isSelected = true;
    } else if (ui->cleanVeryHigh->isChecked()) {
        isSelected = true;
    }
    }

    // Ha nem volt semmi megjelölve, nem engedjük a visszajelzés elküldését, ablak jelenik meg.
    if (!isSelected) {
        QMessageBox::warning(this, "Nothing selected.", "Cannot send review. No rating was given.");
    }

    if (outputFileFB && isSelected) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    outputFileFB << "Timestamp: " << formattedDateTime.toStdString() << endl;
    outputFileFB << "------------------------------" << endl;
    outputFileFB << "Ratings on a scale from 1-5 stars." << endl;

    // Taste of food.
    if (ui->tasteVeryLow->isChecked()) {
        outputFileFB << "Taste of food: 1" << endl;
        ui->tasteVeryLow->setChecked(false);
    } else if (ui->tasteLow->isChecked()) {
        outputFileFB << "Taste of food: 2" << endl;
        ui->tasteLow->setChecked(false);
    } else if (ui->tasteMedium->isChecked()) {
        outputFileFB << "Taste of food: 3" << endl;
        ui->tasteMedium->setChecked(false);
    } else if (ui->tasteHigh->isChecked()) {
        outputFileFB << "Taste of food: 4" << endl;
        ui->tasteHigh->setChecked(false);
    } else if (ui->tasteVeryHigh->isChecked()) {
        outputFileFB << "Taste of food: 5" << endl;
        ui->tasteVeryHigh->setChecked(false);
    }
    // Staff.
    if (ui->staffVeryLow->isChecked()) {
        outputFileFB << "Satisfaction with the staff: 1" << endl;
        ui->staffVeryLow->setChecked(false);
    } else if (ui->staffLow->isChecked()) {
        outputFileFB << "Satisfaction with the staff: 2" << endl;
        ui->staffLow->setChecked(false);
    } else if (ui->staffMedium->isChecked()) {
        outputFileFB << "Satisfaction with the staff: 3" << endl;
        ui->staffMedium->setChecked(false);
    } else if (ui->staffHigh->isChecked()) {
        outputFileFB << "Satisfaction with the staff: 4" << endl;
        ui->staffHigh->setChecked(false);
    } else if (ui->staffVeryHigh->isChecked()) {
        outputFileFB << "Satisfaction with the staff: 5" << endl;
        ui->staffVeryHigh->setChecked(false);
    }
    // Temperature of food.
    if (ui->tempVeryLow->isChecked()) {
        outputFileFB << "Temperature rating of food: 1" << endl;
        ui->tempVeryLow->setChecked(false);
    } else if (ui->tempLow->isChecked()) {
        outputFileFB << "Temperature rating of food: 2" << endl;
        ui->tempLow->setChecked(false);
    } else if (ui->tempMedium->isChecked()) {
        outputFileFB << "Temperature rating of food: 3" << endl;
        ui->tempMedium->setChecked(false);
    } else if (ui->tempHigh->isChecked()) {
        outputFileFB << "Temperature rating of food: 4" << endl;
        ui->tempHigh->setChecked(false);
    } else if (ui->tempVeryHigh->isChecked()) {
        outputFileFB << "Temperature rating of food: 5" << endl;
        ui->tempVeryHigh->setChecked(false);
    }
    // Decoration.
    if (ui->decorVeryLow->isChecked()) {
        outputFileFB << "Love of decoration: 1" << endl;
        ui->decorVeryLow->setChecked(false);
    } else if (ui->decorLow->isChecked()) {
        outputFileFB << "Love of decoration: 2" << endl;
        ui->decorLow->setChecked(false);
    } else if (ui->decorMedium->isChecked()) {
        outputFileFB << "Love of decoration: 3" << endl;
        ui->decorMedium->setChecked(false);
    } else if (ui->decorHigh->isChecked()) {
        outputFileFB << "Love of decoration: 4" << endl;
        ui->decorHigh->setChecked(false);
    } else if (ui->decorVeryHigh->isChecked()) {
        outputFileFB << "Love of decoration: 5" << endl;
        ui->decorVeryHigh->setChecked(false);
    }
    // Cleaniness.
    if (ui->cleanVeryLow->isChecked()) {
        outputFileFB << "Level of cleaniness: 1" << endl;
        ui->cleanVeryLow->setChecked(false);
    } else if (ui->cleanLow->isChecked()) {
        outputFileFB << "Level of cleaniness: 2" << endl;
        ui->cleanLow->setChecked(false);
    } else if (ui->cleanMedium->isChecked()) {
        outputFileFB << "Level of cleaniness: 3" << endl;
        ui->cleanMedium->setChecked(false);
    } else if (ui->cleanHigh->isChecked()) {
        outputFileFB << "Level of cleaniness: 4" << endl;
        ui->cleanHigh->setChecked(false);
    } else if (ui->cleanVeryHigh->isChecked()) {
        outputFileFB << "Level of cleaniness: 5" << endl;
        ui->cleanVeryHigh->setChecked(false);
    }
    outputFileFB << "\n\n-------------------- END OF FEEDBACK --------------------\n\n\n";

    // Fájl bezárása!
    outputFileFB.close();

    resetRadioButtons();
    }
    if (isSelected) {
        // Átirányítás a thank_page oldalra.
        ui->stackedWidget->setCurrentIndex(5);
    }
}


void MainWindow::on_pushBackToMain_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::resetRadioButtons()
{
    // Rádiógombok kijelöltségének eltávolítása
    ui->tasteVeryLow->setAutoExclusive(false);
    ui->tasteLow->setAutoExclusive(false);
    ui->tasteMedium->setAutoExclusive(false);
    ui->tasteHigh->setAutoExclusive(false);
    ui->tasteVeryHigh->setAutoExclusive(false);

    ui->staffVeryLow->setAutoExclusive(false);
    ui->staffLow->setAutoExclusive(false);
    ui->staffMedium->setAutoExclusive(false);
    ui->staffHigh->setAutoExclusive(false);
    ui->staffVeryHigh->setAutoExclusive(false);

    ui->tempVeryLow->setAutoExclusive(false);
    ui->tempLow->setAutoExclusive(false);
    ui->tempMedium->setAutoExclusive(false);
    ui->tempHigh->setAutoExclusive(false);
    ui->tempVeryHigh->setAutoExclusive(false);

    ui->decorVeryLow->setAutoExclusive(false);
    ui->decorLow->setAutoExclusive(false);
    ui->decorMedium->setAutoExclusive(false);
    ui->decorHigh->setAutoExclusive(false);
    ui->decorVeryHigh->setAutoExclusive(false);

    ui->cleanVeryLow->setAutoExclusive(false);
    ui->cleanLow->setAutoExclusive(false);
    ui->cleanMedium->setAutoExclusive(false);
    ui->cleanHigh->setAutoExclusive(false);
    ui->cleanVeryHigh->setAutoExclusive(false);

    // Kijelöltség megszüntetése
    ui->tasteVeryLow->setChecked(false);
    ui->tasteLow->setChecked(false);
    ui->tasteMedium->setChecked(false);
    ui->tasteHigh->setChecked(false);
    ui->tasteVeryHigh->setChecked(false);

    ui->staffVeryLow->setChecked(false);
    ui->staffLow->setChecked(false);
    ui->staffMedium->setChecked(false);
    ui->staffHigh->setChecked(false);
    ui->staffVeryHigh->setChecked(false);

    ui->tempVeryLow->setChecked(false);
    ui->tempLow->setChecked(false);
    ui->tempMedium->setChecked(false);
    ui->tempHigh->setChecked(false);
    ui->tempVeryHigh->setChecked(false);

    ui->decorVeryLow->setChecked(false);
    ui->decorLow->setChecked(false);
    ui->decorMedium->setChecked(false);
    ui->decorHigh->setChecked(false);
    ui->decorVeryHigh->setChecked(false);

    ui->cleanVeryLow->setChecked(false);
    ui->cleanLow->setChecked(false);
    ui->cleanMedium->setChecked(false);
    ui->cleanHigh->setChecked(false);
    ui->cleanVeryHigh->setChecked(false);

    // Ismét engedélyezzük a kizáró működést
    ui->tasteVeryLow->setAutoExclusive(true);
    ui->tasteLow->setAutoExclusive(true);
    ui->tasteMedium->setAutoExclusive(true);
    ui->tasteHigh->setAutoExclusive(true);
    ui->tasteVeryHigh->setAutoExclusive(true);

    ui->staffVeryLow->setAutoExclusive(true);
    ui->staffLow->setAutoExclusive(true);
    ui->staffMedium->setAutoExclusive(true);
    ui->staffHigh->setAutoExclusive(true);
    ui->staffVeryHigh->setAutoExclusive(true);

    ui->tempVeryLow->setAutoExclusive(true);
    ui->tempLow->setAutoExclusive(true);
    ui->tempMedium->setAutoExclusive(true);
    ui->tempHigh->setAutoExclusive(true);
    ui->tempVeryHigh->setAutoExclusive(true);

    ui->decorVeryLow->setAutoExclusive(true);
    ui->decorLow->setAutoExclusive(true);
    ui->decorMedium->setAutoExclusive(true);
    ui->decorHigh->setAutoExclusive(true);
    ui->decorVeryHigh->setAutoExclusive(true);

    ui->cleanVeryLow->setAutoExclusive(true);
    ui->cleanLow->setAutoExclusive(true);
    ui->cleanMedium->setAutoExclusive(true);
    ui->cleanHigh->setAutoExclusive(true);
    ui->cleanVeryHigh->setAutoExclusive(true);
}

