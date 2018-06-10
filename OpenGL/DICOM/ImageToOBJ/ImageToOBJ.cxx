#include "stdio.h"
#include <iostream>
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkTranslationTransform.h"
#include "itkResampleImageFilter.h"
#include <itkShapeLabelMapFilter.h>
#include <sstream>

using namespace  itk;
using namespace  std;


typedef itk::GDCMImageIO ImageIO;
typedef itk::Image<short,3> ImageType;
typedef itk::ImageFileReader<ImageType> ReaderType;


ImageType::Pointer readerImage(string file){
    ImageIO::Pointer imgIO = ImageIO::New();
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(file);
    reader->SetImageIO(imgIO);
    reader->Update();
    return reader->GetOutput();
}

int getMinimum(ImageType::Pointer image){
    typedef MinimumMaximumImageCalculator <ImageType> ImageCalculatorFilterType;
    ImageCalculatorFilterType::Pointer imageCalculatorFilter;
    imageCalculatorFilter = ImageCalculatorFilterType::New ();
    imageCalculatorFilter->SetImage(image);
    imageCalculatorFilter->Compute();
    return imageCalculatorFilter->GetMinimum();
}

void WriteImage(ImageType::Pointer image, int i){
    string s = to_string(i);
    std::ofstream output("/home/alexandre/geometria_comp/OpenGL/DICOM/ImageToOBJ/data/output/Node"+ s + ".obj");
    output << "o Node"+ s + "\n";
    double background = getMinimum(image);
    ImageType::SizeType size = image->GetLargestPossibleRegion().GetSize();

    for(int z = 0; z < size[2]; z++){
        for(int y = 0; y < size[1]; y++){
            for(int x = 0; x < size[0]; x++){
                ImageType::IndexType position;
                position[0] = x;
                position[1] = y;
                position[2] = z;
                if ((int)image->GetPixel(position) != background)
                    output << "v " << position[0] << " " << position[1] << " " << position[2] << "\n";

            }
        }
    }

}


int main(){
    
    for(int i=11; i<=21;i++){
        stringstream path;
        path << "//home/alexandre/geometria_comp/OpenGL/DICOM/ImageToOBJ/data/" <<i<< ".dcm";
        cout << "||------------Nodulo"<<i << ". ----------------|| "<<endl;
        ImageType:: Pointer IMG_IN = readerImage(path.str());
        WriteImage(IMG_IN, i);
    }
    cout << "Hello " << endl;
    return EXIT_SUCCESS;


}
