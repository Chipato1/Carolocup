function edgeImg = sobelEdgeDetectionAlg(img,thresh)
%sobelEdgeDetection Example MATLAB function for edge detection.
% Copyright 2018 The MathWorks, Inc.

kern = [1 2 1; 0 0 0; -1 -2 -1];

% Finding horizontal and vertical gradients.
h = conv2(img(:,:,2),kern,'same');
v = conv2(img(:,:,2),kern','same');

% Finding magnitude of the gradients.
e = sqrt(h.*h + v.*v);

% Threshold the edges
edgeImg = uint8((e > thresh) * 240);

end