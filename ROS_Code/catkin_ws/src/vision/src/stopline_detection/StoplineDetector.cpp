#include  <vision/stopline_detection/StoplineDetector.hpp>


using namespace cv;
using namespace std;

float roiHeight;
float roiWidth;
cv::Mat cdst;
vector<Vec4i> perpendicularLines;
vector<Vec4i> lines;
int validation = 0;

void StoplineDetector::failureReport(string i) {
    cout << "Failed due to: " << i << endl;
}

void StoplineDetector::drawLine (vector<Vec4i> lines) {
    
    for( size_t i = 0; i < lines.size(); i++ )
      {
          Vec4i l = lines[i];
          //cout << "P1: " << Point(l[0], l[1]) << " p" << Point(l[2], l[3]) << endl;
          line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
      }
    
    imshow("detected lines", cdst);
    waitKey();
}

double StoplineDetector::getDistanceBetweenPoints(Point p1, Point p2) {
    return abs(cv::norm(p1-p2));
}

//Check if the line is a stopping or perpendicular line
vector<Vec4i> StoplineDetector::getPossibleEventLine(vector<Vec4i> & detectedLines) {
    vector<Vec4i> possibleStoppLine;
    Vec4i l;
    Point p1, p2;
    float angle;
    
    for( size_t i = 0; i < detectedLines.size(); i++ )
    {
        l = detectedLines[i];
        // draw the lines

        p1=Point(l[0], l[1]);
        p2=Point(l[2], l[3]);
        //calculate angle in radian,  if you need it in degrees just do angle * 180 / PI
        angle = atan2(p1.y - p2.y, p1.x - p2.x) * (180/CV_PI);
        
        if (angle > 170 || angle < 10) {
            possibleStoppLine.push_back(detectedLines.at(i));
        }
        
        if (angle < 100 && angle > 80) {
            perpendicularLines.push_back(detectedLines.at(i));
        }
    }
    
    return possibleStoppLine;
}

vector<Vec4i> StoplineDetector::checkLineWidth (vector<Vec4i> lines) {
        Vec4i l1;
        Vec4i l2;
        double distance1;
        double distance2;
        vector<Vec4i> resultingLines;
        size_t i = 0;
        Point p1;
        Point p2;
        Point p3;
        for (size_t q = 0; q < lines.size()-1; q++) {
            l1 = lines[q];
            p1 = Point(l1[0], l1[1]);
            i++;
            for(;i < lines.size(); i++ )
              {
                  l2 = lines[i];
                  p2 = Point(l2[0], l2[1]);
                  p3 = Point(l2[2], l2[3]);
                  distance1 = getDistanceBetweenPoints(p1, p2);
                  distance2 = getDistanceBetweenPoints(p1, p3);

                  if ((distance1 > 40 && distance1 < 100) || (distance2 > 40 && distance2 < 100)) {
                      resultingLines.push_back(lines[q]);
                      resultingLines.push_back(lines[i]);
                  }
                  
              }
        }
    //    drawLine(resultingLines);
        return resultingLines;
}

cv::Mat StoplineDetector::defineROI (cv::Mat &image) {

    Rect region_of_interest = Rect(image.size().width/4, 0, image.size().width*3/4, image.size().height);
    roiWidth = region_of_interest.size().width;
    roiHeight = region_of_interest.size().height;
    return image(region_of_interest);
}

 Vec4i StoplineDetector::getStopLine (vector<Vec4i> lines) {
    Vec4i i;
     vector<double> distance;
     
     Vec4i l1;
     Point p1;
     Point p2;
     Point carCenter(roiWidth/2, roiHeight);
     double distance1;
     double distance2;
     double min = 0;
     
     Vec4i resultLine;
     
     p1 = Point(l1[0], l1[1]);
     min = getDistanceBetweenPoints(p1, carCenter);
     resultLine = lines[0];
     
     for (size_t q = 0; q < lines.size()-1; q++) {
         l1 = lines[q];
         p1 = Point(l1[0], l1[1]);
         p2 = Point(l1[2], l1[3]);
         
         distance1 = getDistanceBetweenPoints(p1, carCenter);
         distance2 = getDistanceBetweenPoints(p2, carCenter);
         
         
         if (distance1 < min){
             min = distance1;
             resultLine = lines[q];
         }
         
         if (distance2 < min) {
             min = distance2;
             resultLine = lines[q];
         }
     }
      
     return resultLine;
}

vector<Vec4i> StoplineDetector::checkOrthogonal(vector<Vec4i> lines, vector<Vec4i> pLines) {
    vector<Vec4i> resultingLines;
    Vec4i l;
    Vec4i p;
    int m1, m2;
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    float angle;
    
    size_t i = 0;
    for (size_t q = 0; q < pLines.size(); q++) {
        p = pLines[q];
        for(size_t i = 0;i < lines.size(); i++ )
        {
            l = lines[i];
            x1 = l[0];
            y1 = l[1];
            x2 = l[2];
            y2 = l[3];
            
            x3 = p[0];
            y3 = p[1];
            x4 = p[2];
            y4 = p[3];
            
            angle = abs(atan2(y2-y1, x2-x1) - atan2(y4-y3,x4-x3));
            
            angle = angle *180/CV_PI;

            if (angle > 80 && angle < 100 && (x1 < x3 || x2 < x4)) {
                resultingLines.push_back(lines[i]);
            }
        }
    }
    
    return resultingLines;
}


//call by reference
bool StoplineDetector::detect(const vision::HoughPointsArray::ConstPtr &imageArray, int pointerSize) {
	vector<Vec4i> lines;
	Vec4i l;
	for(int i = 0; i < pointerSize; i++){
		const vision::HoughPoints &data = imageArray->points[i];
		l[0] = data.x1;
		l[1] = data.y1;
		l[2] = data.x2;
		l[3] = data.y2;
		lines.push_back(l);
	} 
 

    if (!lines.empty()) {
        lines = getPossibleEventLine(lines);
    }
    else {
if (validation > 0)
	validation--;
           failureReport("1");
           return false;
    }
    
    //eigentlich kann man wenn hier nichts gefunden wird sofort abbrechen !
    if (!lines.empty()) {
        lines = checkLineWidth(lines);
    }
    else{
if (validation > 0)
	validation--;
           failureReport("2");
          return false;
    }
    
//    Check if stoppline is orthogonal to perpendicular
    if (!lines.empty()) {
        lines = checkOrthogonal(lines, perpendicularLines);
    } else{
if (validation > 0)
	validation--;
           failureReport("4");
           return false;
    }
    
    Vec4i stoppLine;
    if (!lines.empty()) {
        stoppLine = getStopLine(lines);
    }
    else{
if (validation > 0)
	validation--;
           failureReport("3");
           return false;
    }
    

    validation++;
	

    if (validation > 4) {
   	return true;
	validation = 0;
    }
}
