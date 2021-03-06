// Vision.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int kernel(int sizeKernel, int pY, int pX, Mat* imageIn, Mat* imageOut) {
	double total = 0;
	for (int y = 0; y < sizeKernel; y++) {
		for (int x = 0; x < sizeKernel; x++) {		
			int current = (int)imageIn->at<uchar>(pY + y, pX + x);
			int mult = (double)current * 1 / 9;
			total += mult;
		}
	}
	
	if (sizeKernel == 5) total / 3; //	normalization

	return total;
}

void smooth(int sizeKernel, Mat* imageIn, Mat* imageOut) {
	*imageOut = imageIn->clone();

	for (int y = 0; y < imageIn->rows - (sizeKernel - 1); y++) {
		for (int x = 0; x < imageIn->cols - (sizeKernel - 1); x++) {
			imageOut->at<uchar>(y, x) = kernel(sizeKernel, y, x, imageIn, imageIn);
		}
	}
}

int kernel(int pY, int pX, Mat* imageIn, Mat* imageOut) {
	
	std::vector<int> pixels;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			pixels.push_back((int)imageIn->at<uchar>(pY + y, pX + x));
		}
	}

	sort(pixels.begin(), pixels.end());	
	return pixels[4];
}

void median(Mat* imageIn, Mat* imageOut) {
	*imageOut = imageIn->clone();

	for (int y = 0; y < imageIn->rows - 2; y++) {
		for (int x = 0; x < imageIn->cols - 2; x++) {
			imageOut->at<uchar>(y, x) = kernel(y, x, imageIn, imageIn);
		}
	}
}

int main()
{
	Mat input = imread("../Pictures/circuitBoard.jfif", IMREAD_GRAYSCALE);
	Mat ret;
	
	median(&input, &ret);

	imshow("input", input);
	imshow("median", ret);

	waitKey(0);
    std::cout << "Hello World!\n"; 
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
