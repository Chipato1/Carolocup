cam = webcam(hwobj);
for i = 1:200
    img = snapshot(cam);
    thersh = 100;
    edgeImage = sobelEdgeDetectionAlg(img, thersh); 
    image(dispObj,edgeImage);
end