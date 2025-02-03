// FCAI – Structured Programming CS112 – 2024 - Assignment 3
// File:    CS112_A3_Part2B_Section 5_20230353_20230289_20230294.cpp
// Purpose: Mini Photoshop has 12 different filter
// Last Modification Date: 14/4/2024

// Author1 and ID and Group: Mohamed Magdy Anwar - 20230353 - Section 5
// Author2 and ID and Group: Klara Sameh Wadie - 20230294 - Section 5
// Author3 and ID and Group: Katren Nader Nagy - 20230289 - section 5
// Teaching Assistant: Rana Abdelkader

// Mohamed Magdy  -> Filter 3 , 6 , 9 , 12 , Purple(16)
// Klara Sameh   -> Filter 2 , 5 , 8 , 11 , Sunlight(13)
// Katren Nader  -> Filter 1 , 4 , 7 , 10 , Infrared(17)

// Emails:mohamedmagdy6674@gmail.com
//        katrennader16@gmail.com
//        klarasameh39@gmail.com

//GitHub Repo : https://github.com/Cancelo13/S5-Assign3
//System diagram : https://drive.google.com/drive/folders/1owFaeGKxvpTZba65mOlt2vF8eJSoKcfS?usp=sharing

#include <vector>
#include "Image_Class.h"
using namespace std;

Image filter1(Image& image); // GrayScale filter

Image filter2(Image& image); //Black and White filter
int black_white_filter(unsigned int value, unsigned int conversionvalue);
unsigned int rgb_to_gray(unsigned int r, unsigned int g, unsigned int b);

Image filter3(Image& image ); //Invert colors filter

Image filter4(Image& image, Image& image2); // Merge

Image filter5(Image& image , char choice); // Flipping filter

Image filter6(Image& image , string optionD , Image& image_R ); // Rotating filter

Image filter7(Image& image,double degree); // Darkness and lightness filter

Image filter8(Image& image,int xstart , int ystart, int croped_width,int croped_hieght); //crop

Image filter9(Image& image , const string& color , char th); //Simple frame
Image filter9(Image& image); //fancy frame

Image filter10(Image& image); //Edge

Image filter11(Image& image,int newW,int newH); // resize
Image filter11R(Image& image, double ratio); // resize with ratio

Image filter12(Image& image , int r); // blur

Image filter_Purple(Image& image); //Purple

Image filter_Infrared(Image& image); //Infrared

Image filter_Sunlight(Image& image); //Sunlight

bool valid(const string& name); // check if the file exists
bool save_valid(string name); // check if the save is valid
void save(Image& image , Image& Cimage , const string& name); // save files

int main() {
    string si , s , name , option; // initialize strings for options in the whole program
    while (true) { // Main menu
        cout << "***Image processing Program***" << endl << "A)Load New Image\n" << "B)Exit\n" << endl;
        cout << "Choose your option : ";
        cin>>s;

        Image image; // initialize the image
        if (s.length() == 1 &&(s == "A" || s == "a" || s == "1")) {
            while(true) {
                cout<<endl<<"Enter Image file name:";
                cin.ignore();
                getline(cin,name);
                cout<<endl;
                if(valid(name)) { // check if the file is existed or not
                    image.loadNewImage(name);
                    break;
                }else{
                    cout<<"Please make sure you have insert a valid file name!"<<endl;
                }
            }
            Image image_R(image.height,image.width); // initialize new empty image for rotating
            Image Cimage = image; // initialize new image that will be used in the undo operation
            while (true) { //Options menu
                cout << "\nA)GrayScale\n" << "B)Black and White\n" << "C)Invert\n"
                     << "D)Merge Images\n"<< "E)Flip Image\n" << "F)Rotating\n" << "G)Darken and Lighten Image\n"
                     << "H)Crop Images\n"<< "I)Adding a Frame\n" << "J)Detect Image Edges\n"<< "K)Resizing Images\n"
                     << "L)Blur Images\n"<<"M)Purple filter\n"<<"N)Infrared filter\n"<<"O)Sunlight filter\n"
                     << "-Load New image (Press 0)" << endl
                     <<"-Save Image (Type \"Save\")\n"<<"-Undo (Type \"Undo\")\n"<<"-Exit (Type \"Exit\")\n"<<endl;
                cout << "Choose an option from the list : ";
                cin >> si;
                cout << endl;
                if(si.length() == 1 && si == "0"){ // Load new image
                    string _name , p;
                    while(true) {
                        cout << "Do you want to save the current image before load new one? (Yes or No)";
                        cin >> p;
                        if (p == "yes" || p == "Yes" || p == "YES") { // save before load
                            save(image, Cimage, name);
                            cout << "\nSuccessfully saved the image" << endl;
                            while(true) { // check if valid or not
                                cout << "Insert the New image Now: ";
                                getline(cin,_name);
                                if(valid(_name)) {
                                    image.loadNewImage(_name);
                                    cout<<"\nNew image has been uploaded successfully"<<endl;
                                    break;
                                }else{
                                    cout<<"\nPlease make sure you have insert a valid file name!"<<endl;
                                }
                            }
                            break;
                        } else if (p == "NO" || p == "No" || p == "no") {
                            while(true) { // check if valid or not
                                cout << "\nInsert the New image Now: ";
                                cin.ignore();
                                getline(cin,_name);
                                if (valid(_name)) {
                                    image.loadNewImage(_name);
                                    cout<<"\nNew image has been uploaded successfully"<<endl;
                                    break;
                                } else {
                                    cout << "\nPlease make sure you have insert a valid file name!" << endl;
                                }
                            }
                            break;

                        } else {
                            cout << "\nWrong option, try again" << endl;
                        }
                    }
                }else if (si.length() == 1 && (si == "a" || si == "A")) { // GrayScale
                    Cimage = image;
                    image = filter1(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                } else if (si.length() == 1 && (si == "b" || si == "B" )) { // Black and white
                    Cimage = image;
                    image = filter2(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                } else if (si.length() == 1 &&(si == "C" || si == "c" )) { // Invert
                    Cimage = image;
                    image = filter3(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                } else if (si.length() == 1 &&(si == "D" || si == "d")){ // Merge
                    Cimage = image;
                    Image image2;
                    string name2;
                    while(true) {
                        cout<<"\nEnter Second Image file name: ";
                        cin.ignore();
                        getline(cin,name2);
                        cout<<endl;
                        if(valid(name2)) { // check if the file is existed or not
                            image2.loadNewImage(name2);
                            break;
                        }else{
                            cout<<"Please make sure you have insert a valid file name!"<<endl;
                        }
                    }
                    image = filter4(image,image2);
                    cout << "\nThe filter has been applied successfully" << endl;
                }else if (si.length() == 1 && (si == "e" || si == "E")) { // Flip
                    string choice;
                    while (true) {
                        cout << "A)Horizontally\nB)vertically\nchoose(A/B): ";
                        cin >> choice;
                        if (choice.length()==1 && (choice == "A" || choice == "a" )) {
                            Cimage = image;
                            image = filter5(image, 'A');
                            break;
                        } else if (choice.length()==1 && (choice == "B" || choice == "b" )) {
                            Cimage = image;
                            image = filter5(image, 'B');
                            break;
                        } else {
                            cout << "\nWrong choice, Please insert a valid one" << endl;
                        }
                    }
                    cout << "\nThe filter has been applied successfully" << endl;
                } else if (si.length() == 1 &&(si == "f" || si == "F")) { // Rotate
                    string optionR , optionD;
                    while (true) {
                        cout << "List of degrees" << endl;
                        cout << "A)Rotate 90 degree\n" << "B)Rotate 180 degree\n" << "C)Rotate 270 degree\n"
                             << endl;
                        cout << "Choose your option: ";
                        cin >> optionD;
                        cout << endl;
                        if (optionD.length() == 1 && (optionD == "a" || optionD == "A" )) { // 90 degree
                            Cimage = image;
                            image = filter6(image, "A", image_R);
                            break;
                        } else if (optionD.length() == 1 &&(optionD == "b" || optionD == "B" || optionD == "2")) { // 180
                            Cimage = image;
                            image = filter6(image, "B", image_R);
                            break;
                        } else if (optionD.length() == 1 &&(optionD == "C" || optionD == "c" || optionD == "3")) { // 270
                            Cimage = image;
                            image = filter6(image, "C", image_R);
                            break;
                        } else {
                            cout << "\nWrong Degree, Please insert a Valid Degree!" << endl;
                        }
                    }
                    cout << "\nThe filter has been applied successfully" << endl;
                } else if (si.length() == 1 &&(si == "G" || si == "g" || si == "7")) { // Darkness and lighten
                    string ss;
                    while (true) {
                        cout << "A)Darkness\n" << "B)Lighten\n";
                        cout << "Choose a filter: ";
                        cin >> ss;
                        if (ss == "A" || ss == "a" || ss == "1") {
                            Cimage = image;
                            image = filter7(image, 0.5);
                            break;
                        } else if (ss == "B" || ss == "b" || ss == "2") {
                            Cimage = image;
                            Cimage = filter7(image, 1.5);
                            break;
                        } else {
                            cout << "\nWrong type, Please insert a valid type" << endl;
                        }
                    }
                    cout << "\nThe filter has been applied successfully" << endl;
                }else if(si.length() == 1 &&(si == "H" || si == "h")){
                    int Xstart,Ystart,cropped_width,cropped_height;
                    Cimage = image;
                    while(true) {
                        cout << "Enter the starting point coordinates(x,y):\nX:";
                        cin >> Xstart;
                        if(Xstart < image.width && Xstart > 0){
                            while(true) {
                                cout << "Y:";
                                cin >> Ystart;
                                if (Ystart > 0 && Ystart < image.height) {
                                    while(true) {
                                        cout << "Enter the dimensions:\nW:";
                                        cin >> cropped_width;
                                        if(cropped_width < image.width && cropped_width > 0){
                                            while(true) {
                                                cout << "H:";
                                                cin >> cropped_height;
                                                if(cropped_height < image.height && cropped_height > 0){
                                                    image = filter8(image,Xstart,Ystart,cropped_width,cropped_height);
                                                    cout << "\nThe filter has been applied successfully" << endl;
                                                    break;
                                                }else{
                                                    cout<<"Wrong dimensions point, Please make sure you have input a valid one";
                                                }
                                            }
                                            break;
                                        }else{
                                            cout<<"Wrong dimensions point, Please make sure you have input a valid one";
                                        }
                                    }
                                    break;
                                }else{
                                    cout<<"Wrong start point, Please make sure you have input a valid one";
                                }
                            }
                            break;
                        }else{
                            cout<<"Wrong start point, Please make sure you have input a valid one";
                        }
                    }
                }
                else if (si.length() == 1 &&(si == "I" || si == "i" )) { // Frame
                    string op, th;
                    string color;
                    while (true) {
                        cout << "Frame list:\n" << "A)Simple\n" << "B)Fancy\n"<<"Choose frame type :";
                        cin >> op;
                        if (op.length() ==1 && ( op == "A" || op == "a")) { // get the color
                            while(true) {
                                cout << endl << "\nColors list: \n" << "A)Red\n" << "B)Blue\n" << "C)Green\n"
                                     << "D)Light Purple\n"
                                     << "E)Baby blue\n" << "F)Dark Pink\n" << "G)Metallic Silver" << endl;
                                cin >> color;
                                if(color.length() == 1 && (color =="A" || color == "a" || color == "B"|| color == "b"
                                                           || color == "C" || color == "c" || color == "D" || color == "d" || color == "E" || color == "e"
                                                           || color == "F" || color == "f" || color == "g" || color == "G")){
                                    break;
                                }else{
                                    cout<<"Please make sure you have chosen an valid color"<<endl;
                                }
                            }
                            while (true) { //get the thickness level
                                cout << "\nthickness List: \n" << "A)Small\n" << "B)Medium\n" << "C)Large\n";
                                cout << "Choose thickness level: ";
                                cin >> th;
                                if (th.length() ==1 &&( th == "A" || th == "a" )) { // small
                                    Cimage = image;
                                    image = filter9(image, color, 'A');
                                    break;
                                } else if (th.length() ==1 &&(th == "B" || th == "b" )) { // medium
                                    Cimage = image;
                                    image = filter9(image, color, 'B');
                                    break;
                                } else if (th.length() ==1 &&(th == "C" || th == "c")) { // large
                                    Cimage = image;
                                    image = filter9(image, color, 'C');
                                    break;
                                } else {
                                    cout << "\nWrong thickness level, Please insert a valid one!" << endl;
                                }
                            }
                            break;
                        } else if (op.length()==1 &&( op == "B" || op == "b" )) {
                            Cimage = image;
                            image = filter9(image);
                            break;
                        } else {
                            cout << "\nWrong Frame type, Please choose a valid one!" << endl;
                        }
                    }
                    cout << "\nThe filter has been applied successfully" << endl;

                }else if (si.length() == 1 &&(si == "J" || si == "j" )){ // Detect Edges
                    Cimage = image;
                    image = filter10(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                }
                else if (si.length() == 1 &&(si == "K" || si == "k" )){ //Resize
                    string choice;
                    cout<<"choose how you want to resize:\nA)By dimensions\nB)By ratio\nEnter your choice (A/B):";
                    cin>>choice;
                    Cimage = image;
                    //Resizing by dimensions
                    if (choice.length() == 1 && (choice=="A"||choice=="a")) {
                        int newW, newH;
                        Cimage = image;
                        cout << "Enter the dimensions\nW:";
                        cin >> newW;
                        cout << "H:";
                        cin >> newH;
                        image = filter11(image,newW,newH);
                        cout << "\nThe filter has been applied successfully" << endl;

                    }else if(choice.length() == 1 && (choice=="B"||choice=="b")){
                        double ratio;
                        while(true) {
                            cout << "Enter the ratio (%) :";
                            cin >> ratio;
                            if(ratio > 0) {
                                ratio /= 100.0;
                                image = filter11R(image, ratio);
                                cout << "\nThe filter has been applied successfully" << endl;
                                break;
                            }else{
                                cout<<"Wrong ratio, Please make sure you have input a valid one"<<endl;
                            }
                        }
                    }
                    cout << "\nThe filter has been applied successfully" << endl;
                }else if(si.length() == 1 &&(si == "L" || si == "l" )){ //Blur
                    Cimage = image;
                    string blur;
                    int r = 0;
                    while(true) {
                        cout << "A)Light Blur\n" << "B)Medium Blur\n" << "C)Hard Blur\n";
                        cout << "Choose Blur level: ";
                        cin >> blur;
                        if (blur.length() == 1 && (blur == "A" || blur == "a")) {
                            r = 5;
                            image = filter12(image , r);
                            cout << "\nThe filter has been applied successfully" << endl;
                            break;
                        } else if (blur.length() == 1 && (blur == "B" || blur == "b")) {
                            r = 10;
                            image = filter12(image,r);
                            cout << "\nThe filter has been applied successfully" << endl;
                            break;
                        } else if (blur.length() == 1 && (blur == "C" || blur == "c")) {
                            r = 20;
                            image = filter12(image,r);
                            cout << "\nThe filter has been applied successfully" << endl;
                            break;
                        }else{
                            cout<<"Wrong option, Please make sure you have input a Valid one"<<endl;
                        }
                    }
                }else if(si.length() == 1 &&(si == "M" || si == "m" )){
                    Cimage = image;
                    image = filter_Purple(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                }else if(si.length() == 1 &&(si == "N" || si == "n" )){
                    Cimage = image;
                    image = filter_Infrared(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                }else if(si.length() == 1 &&(si == "O" || si == "o" )){
                    Cimage = image;
                    image = filter_Sunlight(image);
                    cout << "\nThe filter has been applied successfully" << endl;
                }
                else if(si == "Save" || si == "SAVE" || si == "save"){ // save
                    save(image,Cimage,name);
                    cout<<"Successfully saved the image"<<endl;
                }else if(si == "Undo" || si == "undo" || si == "UNDO") { // Undo (max one step back)
                    string sure;
                    while(true) {
                        cout << "Only one step back , are you sure? (Yes or No): ";
                        cin >> sure;
                        if (sure == "Yes" || sure == "YES" || sure == "yes") {
                            image = Cimage; // undo by make the image equals to the Cimage
                            cout << "You have undid one filter" << endl;
                            break;
                        } else if (sure == "NO" || sure == "No" || sure == "no") {
                            cout << "Returning to the main menu" << endl;
                            break;
                        } else {
                            cout << "Wrong option , try again" << endl;
                        }
                    }
                }
                else if(si == "Exit" || si == "exit" || si == "EXIT" ){ //Exit
                    cout<<"\nReturning to the Main Menu"<<endl;
                    break;
                }
            }
        } else if (s.length() == 1 && (s == "B" || s=="b" || s=="2")) { //Exit the whole program
            cout << "\nThanks for using our simple photoshop <3 ";
            break;
        } else {
            cout << "Wrong option" << endl;
        }
    }
}

Image filter1(Image& image) { // GrayScale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) { // divide the avg of colors of each pixel by 3
                avg += image(i, j, k);
            }
            unsigned int Navg = avg / 3;
            for (int k = 0; k < 3; ++k) { // apply the new avg
                image(i, j, 0) = Navg;
                image(i, j, 1) = Navg;
                image(i, j, 2) = Navg;
            }
        }
    }
    return image;
}

int black_white_filter(unsigned int value, unsigned int conversionvalue) {
    return (value > conversionvalue) ? 255 : 0; // If value > conversionvalue, return 255 (white), else return 0 (black)
}
unsigned int rgb_to_gray(unsigned int r, unsigned int g, unsigned int b) {
    return (r + g + b) / 3; // Simple average method
}
Image filter2(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int conversionvalue = 127;
            unsigned int avg = rgb_to_gray(image(i, j, 0), image(i, j, 1), image(i, j, 2));
            unsigned int bw = black_white_filter(avg, conversionvalue);

            // Set all channels to the same value for black and white
            image(i, j, 0) = bw;
            image(i, j, 1) = bw;
            image(i, j, 2) = bw;
        }
    }
    return image;
}

Image filter3(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) { // invert by subtract the average for each pixel from 255
                image(i,j,k) = 255 - image(i,j,k);
            }
        }
    }
    return  image;
}

Image filter4(Image& image , Image& image2){
    Image imageM = image;
    Image image3 = filter11(image2,image.width,image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for(int k=0;k<3;k++){
                imageM(i,j,k)= (image3(i,j,k)+image(i,j,k))/2;   // finally add image 1 and image 2 (resized image)
            }
        }
    }
    return imageM;
}

Image filter5(Image& image , char choice){ // flip filter
    if (choice == 'A' || choice == 'a' || choice == '1') {
        for (int i = 0; i < image.width / 2; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) { // swap to rotate it Horizontally
                    swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }
    } else if (choice == 'B' || choice == 'b' || choice == '2') { // swap to rotate it vertically
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    }
    return image;
}

Image filter6(Image& image , string optionD , Image& image_R ) {
    if (optionD.length() ==1 && (optionD == "a" || optionD == "A" || optionD == "1")) { // 90 degree
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) { // rotate it to make it 270 degree
                    image_R(j, i, k) = image(i, j, k);
                }
            }
        }
        for (int i = 0; i < image_R.width / 2; i++) { // flip it to make it 90 degree
            for (int j = 0; j < image_R.height; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image_R(i, j, k), image_R(image_R.width - i, j, k));
                }
            }
        }
        return image_R;
    } else if (optionD.length() ==1 &&(optionD == "b" || optionD == "B" || optionD == "2")) { // 180
        image_R = image;
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) { // flip it to make it rotated 180
                for (int k = 0; k < 3; k++) {
                    swap(image_R(i, j, k), image_R(i, image.height - j - 1, k));
                }
            }
        }
        return image_R;
    }else if (optionD.length() ==1 &&(optionD == "C" || optionD == "c" || optionD == "3")) { // 270
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) { // rotate to make it 270
                for (int k = 0; k < 3; k++) {
                    image_R(j, i, k) = image(i, j, k);
                }
            }
        }
        return image_R;
    }
}

Image filter7(Image& image,double degree){ // darkness and lighten
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {     // channels =3
                unsigned int new_darkness_degree = image(i, j, k) * degree; // degree based on the option
                if(new_darkness_degree >= 255) new_darkness_degree = 255; // not make the avg above 255
                else if(new_darkness_degree <= 0) new_darkness_degree = 0; // not make the avg under 0
                image(i, j, k) = new_darkness_degree; // make the pixel based on the degree
            }
        }
    }
    return image;
}

Image filter8(Image& image,int xstart , int ystart, int croped_width,int croped_hieght){
    Image croppedImage(croped_width,croped_hieght); //creating new image with the new diminsions
    //copy pixels from the original image
    for (int i = 0; i < croped_width; i++) { // x-axis
        for (int j = 0; j < croped_hieght; j++) { //y-axis
            int X = xstart + i;
            int Y = ystart + j;
            for (int c = 0; c < 3; c++) {
                unsigned char value = image.getPixel(X, Y, c);
                croppedImage(i, j, c) = value;
            }
        }
    }
    // restore the cropped image in the original one
    return croppedImage;
}

Image filter9(Image& image , const string& color , char th){ //simple frame
    unsigned int avgR =0 , avgB=0,avgG =0;
    if(color.length()==1 && (color == "A" || color == "a" || color =="1")) avgR=255,avgB=0,avgG=0; // RED
    else if(color.length()==1 &&(color == "B" || color == "b" || color =="2")) avgR=0,avgB=255,avgG=0; //Blue
    else if(color.length()==1 &&(color == "C" || color == "c" || color =="3")) avgR =0,avgB=0,avgG=255; // Green
    else if(color.length()==1 &&(color == "D" || color == "d" || color =="4")) avgR =160,avgG=32,avgB=240; // Purple
    else if(color.length()==1 &&(color == "E" || color == "e" || color =="5")) avgR =173,avgG=216,avgB =230; // Baby blue
    else if(color.length()==1 &&(color == "F" || color == "f" || color =="6")) avgR = 255,avgG = 105, avgB = 180; //Deep Pink
    else if(color.length()==1 &&(color =="G" || color =="g" || color =="7")) avgG = avgB = avgR = 192; // Metallic silver

    if(th == 'A' || th == 'a' || th == '1'){ // small frame
        for(int i = 0 ; i < image.width ; i++){
            for(int j = 0 ; j < image.height * 2.5/100 ; j++) { // iterate to make the upper width as a frame
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width* 2.5/100 ; i++){ // iterate on the left side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = image.width -1 ; i >= image.width* (100-2.5)/100 ; i--){ // iterate on the lower side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width ; i++){
            for(int j = image.height -1 ; j >= image.height * (100-2.5)/100 ; j--) { // iterate on the right side of the image
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
    }else if(th == 'B' || th =='b' || th == '2'){
        for(int i = 0 ; i < image.width ; i++){
            for(int j = 0 ; j < image.height * 5/100 ; j++) {  // iterate to make the upper width as a frame
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width* 5/100 ; i++){ // iterate on the left side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = image.width -1 ; i >= image.width* (100-5)/100 ; i--){ // iterate on the lower side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width ; i++){
            for(int j = image.height -1 ; j >= image.height * (100-5)/100 ; j--) { // iterate on the right side of the image
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
    }else if(th == 'C' || th =='c' || th == '3') {
        for(int i = 0 ; i < image.width ; i++){
            for(int j = 0 ; j < image.height * 7.5/100 ; j++) { // iterate to make the upper width as a frame
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width* 7.5/100 ; i++){ // iterate on the left side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = image.width -1 ; i >= image.width* (100-7.5)/100 ; i--){ // iterate on the lower side of the image
            for(int j = 0 ; j < image.height ; j++) {
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
        for(int i = 0 ; i < image.width ; i++){
            for(int j = image.height -1 ; j >= image.height * (100-7.5)/100 ; j--) { // iterate on the right side of the image
                image(i, j, 0) = avgR;
                image(i, j, 1) = avgG;
                image(i, j, 2) = avgB;
            }
        }
    }
    return image;
}
Image filter9(Image& image){
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 10 ; j < 20 ; j++) { // iterate to make the upper width as a frame
            for(int k = 0 ; k < 3 ;k++){
                image(i,j,k) = 255;
            }
        }
    }
    for(int i = 10 ; i < 20; i++){ // iterate on the left side of the image
        for(int j = 0 ; j < image.height ; j++) {
            for(int k = 0 ; k < 3 ;k++){
                image(i,j,k) = 255;
            }
        }
    }
    for(int i = 0 ; i < image.width ; i++){ // iterate on the lower side of the image
        for(int j = image.height- 20 ; j < image.height - 10 ; j++) {
            for(int k = 0 ; k < 3 ;k++){
                image(i,j,k) = 255;
            }
        }
    }
    for(int i = image.width -20 ; i < image.width - 10 ; i++){
        for(int j = 0 ; j < image.height  ; j++) { // iterate on the right side of the image
            for(int k = 0 ; k < 3 ;k++){
                image(i,j,k) = 255;
            }
        }
    }
    return image;
}

Image filter10(Image& image){
    int x_coordinate = 0;    // stores intensity  on x-axis (horzintal gradient))
    int y_coordinate =0;    //stores intensity on Y-axis  (vertical gradient))

    Image Detected_Image(image.width, image.height);     // make new image to hold image after edge detection

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (i > 0 && i < image.width - 1) {// moves on x coordinate

                    x_coordinate = image (i+1,j,k) - image(i-1,j,k);  // Calculate intensity difference for  horizontal gradient

                } if (j > 0 && j < image.height - 1){    // moves on y coordinate

                    y_coordinate = image (i,j+1,k) - image(i,j-1,k); // Calculate intensity difference for vertical gradient

                }
                // calculate magnitude of total sobel of (x,y)
                int total_sobel = sqrt(x_coordinate*x_coordinate + y_coordinate*y_coordinate);
                // calculate threshold value
                const int  threshold_value=50 ;    // constant value for threshold

                if (  total_sobel > threshold_value){
                    Detected_Image(i, j, k) = 0; // change edge into black  color
                }else  {
                    Detected_Image(i, j, k) = 255; // change edge to white  color
                }
            }
        }
    }
    Detected_Image = filter2(Detected_Image);
    return Detected_Image;
}

Image filter11(Image& image,int newW,int newH){
    double Width_ratio  = (double)newW/image.width  ;
    double Height_ratio = (double)newH/image.height ;

    //calculate new width and new height
    newW=(int)(image.width*Width_ratio) ;
    newH=(int)(image.height*Height_ratio);

    Image resizedImage(newW, newH); //create new image with desiered diminsions
    for (int x = 0; x < newW; x++) {
        for (int y = 0; y < newH; y++) {
            //Calculate corresponding y coordinate in the original image
            double Y = (double)y / Height_ratio;
            int resizedY = (int)floor(Y); //Floor to get the closest integer

            //Calculate corresponding x coordinate in the original image
            double X = (double)x / Width_ratio;
            int resizedX = (int)floor(X);//Floor to get the closest integer

            // Check if coordinates are within original image bounds
            if (resizedX >= 0 && resizedX < image.width && resizedY >= 0 && resizedY < image.height) {
                // Access and set pixel values for each channel
                for (int c = 0; c < 3; c++) {
                    unsigned char value = image(resizedX, resizedY, c);
                    resizedImage(x, y, c) = value;
                }
            }
        }
    }
    return resizedImage;
}
Image filter11R(Image& image, double ratio){
    int newW=(int)(image.width*ratio );
    int newH=(int)(image.height*ratio);

    Image resizedImage(newW, newH); //create new image with desiered diminsions

    for (int y = 0; y < newH; y++) {
        for (int x = 0; x < newW; x++) {
            // Calculate corresponding y coordinate in the original image
            double originalY = (double)y / ratio;
            int resizedY = (int)floor(originalY);// Floor to get the closest integer

            // Calculate corresponding x coordinate in the original image based on ratio
            double originalX = (double)x / ratio;
            int resizedX = (int)floor(originalX);// Floor to get the closest integer

            // Check if coordinates are within original image bounds
            if (resizedX >= 0 && resizedX < image.width && resizedY >= 0 && resizedY < image.height) {
                // Access and set pixel values for each channel
                for (int c = 0; c< 3; c++) {
                    unsigned char value = image.getPixel(resizedX, resizedY, c);
                    resizedImage.setPixel(x, y, c, value);
                }
            }
        }
    }
    return resizedImage;
}
Image filter12(Image& image , int r) {
    int width = image.width, height = image.height;
    Image imageBB(width, height); // Initialize the output image

    vector<vector<int>> redPref(width, vector<int>(height, 0));
    vector<vector<int>> greenPref(width, vector<int>(height, 0));
    vector<vector<int>> bluePref(width, vector<int>(height, 0));

    for (int j = 0; j < width; j++) {
        redPref[j][0] = image(j, 0, 0);
        greenPref[j][0] = image(j, 0, 1);
        bluePref[j][0] = image(j, 0, 2);
        if (j > 0) {
            redPref[j][0] += redPref[j - 1][0];
            greenPref[j][0] += greenPref[j - 1][0];
            bluePref[j][0] += bluePref[j - 1][0];
        }
    }
    for (int i = 1; i < height; i++) {
        redPref[0][i] = redPref[0][i - 1] + image(0, i, 0);
        greenPref[0][i] = greenPref[0][i - 1] + image(0, i, 1);
        bluePref[0][i] = bluePref[0][i - 1] + image(0, i, 2);
    }

    for (int i = 1; i < width; i++) {
        for (int j = 1; j < height; j++) {
            redPref[i][j] = redPref[i - 1][j] + redPref[i][j - 1] - redPref[i - 1][j - 1] + image(i, j, 0);
            greenPref[i][j] = greenPref[i - 1][j] + greenPref[i][j - 1] - greenPref[i - 1][j - 1] + image(i, j, 1);
            bluePref[i][j] = bluePref[i - 1][j] + bluePref[i][j - 1] - bluePref[i - 1][j - 1] + image(i, j, 2);
        }
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int BeginX = max(0, i - r), BeginY = max(0, j - r);
            int EndX = min(width - 1, i + r), EndY = min(height - 1, j + r);
            int area = (EndY - BeginY + 1) * (EndX - BeginX + 1);
            int redSum = redPref[EndX][EndY], greenSum = greenPref[EndX][EndY], blueSum = bluePref[EndX][EndY];
            if(BeginX > 0){
                redSum -= redPref[BeginX - 1][EndY];
                greenSum -= greenPref[BeginX - 1][EndY];
                blueSum -= bluePref[BeginX - 1][EndY];
            }
            if(BeginY > 0){
                redSum -= redPref[EndX][BeginY - 1];
                greenSum -= greenPref[EndX][BeginY - 1];
                blueSum -= bluePref[EndX][BeginY - 1];
            }
            if(BeginX > 0 && BeginY > 0){
                redSum += redPref[BeginX - 1][BeginY - 1];
                greenSum += greenPref[BeginX - 1][BeginY - 1];
                blueSum += bluePref[BeginX - 1][BeginY - 1];
            }

            imageBB(i, j, 0) = redSum / area;
            imageBB(i, j, 1) = greenSum / area;
            imageBB(i, j, 2) = blueSum / area;
        }
    }

    return imageBB;
}
Image filter_Purple(Image& image){
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            image(i,j,0) = min(255,int(image(i,j,0)*1.2)); //red
            image(i,j,1) = min(255,int(image(i,j,1)*0.7)); //green
            image(i,j,2) = min(255,int(image(i,j,2)*1.2)); //blue
        }
    }
    return image;
}
Image filter_Infrared(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned char  newred = image(i,j,0);
            image (i,j,0)=255 ;//red
            image(i,j,1)=255-newred; //green
            image(i,j,2)=255-newred; //blue

        }
    }
    return image;
}
Image filter_Sunlight(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i,j,2) *=0.7 ;   //Blue
        }
    }
    return image;
}
void save(Image& image , Image& Cimage,const string& name){ //Save images
    string option;
    while(true) {
        cout << "Do you want to save in the same file ? (Yes or No): ";
        cin >> option;
        if (option == "Yes" || option == "YES" || option == "yes") {
            image.saveImage(name); //save in the same file
            Cimage = image;
            break;
        } else if (option == "No" || option == "NO" || option == "no") {
            string output;
            while(true) {
                cout << "\nEnter the new file name and specify extension (.jpg, .bmp, .png, .tga): ";
                cin >> output;
                if(save_valid(output)) { // check if the name is valid or not
                    image.saveImage(output); // save on the new name
                    Cimage = image;
                    break;
                }else{
                    cout<<"\nPlease make sure you have insert a valid file name!"<<endl;
                }
            }
            break;
        } else {
            cout << "\nWrong option, please try again" << endl;
        }
    }
}
bool valid(const string& name){ // Valid function
    FILE* file = fopen(name.c_str(),"r"); //pointer that points on the file with name that user give it
    // to make sure if the file is existed or not , by pointing on it
    // and try to open it .
    if(file != nullptr) return true; // if the pointer doesn't point on any file, that means the user input is wrong
    else return false;
}
bool save_valid(string name){ // Save validation
    string ex; // check if the extension is correct
    for(int i = 0 ; i < name.size(); i++){// get the extension from the input name
        if(name[i] =='.'){
            ex = name.substr(i+1,name.size()- i - 1);
            break;
        }
    }
    if(ex =="png" || ex=="jpg" || ex == "bmp" || ex =="tga") return true; // check if it's matching the types or not
    else return false;
}
