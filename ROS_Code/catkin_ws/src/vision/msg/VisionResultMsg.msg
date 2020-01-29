float64[4] leftLane1    #Erster Teil der linken Klothoide (Reihenfolge: c1, c0, phi, delta x)
float64[4] middleLane1  #Erster Teil der mittleren Klothoide
float64[4] rightLane1   #Erster Teil der rechten Klothoide

float64[4] leftLane2    #Erster Teil der linken Klothoide
float64[4] middleLane2  #Erster Teil der mittleren Klothoide
float64[4] rightLane2   #Erster Teil der rechten Klothoide

float64 clothoideCutDistanceL_mm;    #Distanz, bei der beide linken Klothoiden getrennt sind.
float64 clothoideCutDistanceM_mm;    #Distanz, bei der beide mittleren Klothoiden getrennt sind.
float64 clothoideCutDistanceR_mm;    #Distanz, bei der beide rechten Klothoiden getrennt sind.

bool foundLL    #Linke Spur gefunden?
bool foundML
bool foundRL

bool solvedLL1  #1. Teil der linken Spur gelöst? (Gibt an, ob leftLane1 valide Werte enthält)
bool solvedML1  
bool solvedRL1

bool solvedLL2  #2. Teil der linken Spur gelöst? (Gibt an, ob leftLane2 valide Werte enthält)
bool solvedML2
bool solvedRL2

bool oppositeLane   #Fährt das Auto im Gegenverkehr? (Experimental, nicht getestet)
