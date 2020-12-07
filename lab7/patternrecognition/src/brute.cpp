/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <map>
// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void fast(Point point, vector<Point>& points);
map<double, vector<Point>> slopes;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input150.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();
//*
    vector<Point> pointsCopy = points;
    for(auto point : points){ //O(N)
        if(points.size() > 0){
            fast(point, pointsCopy);
            pointsCopy.erase(pointsCopy.begin());

            for(auto pair : slopes){
                if(pair.second.size() > 3){

                    for(unsigned int i = 0; i<pair.second.size()-1; i++){
                        render_line(scene, pair.second[i], pair.second[i+1]);
                        a.processEvents(); // show rendered line
                    }
                }
            }
            slopes.clear();
           }
    }


/*

    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N-3 ; ++i) {
        for (int j = i+1 ; j < N-2 ; ++j) {
            for (int k = j+1 ; k < N-1 ; ++k) {
                //only consider fourth point if first three are collinear
                if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(k))) {
                    for (int m{k+1} ; m < N ; ++m) {
                        if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(m))) {
                            render_line(scene, points.at(i), points.at(m));
                            a.processEvents(); // show rendered line
                        }
                    }
                }
            }
        }
    }
    //*/

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}

void fast(Point point, vector<Point>& points){
    for(auto p : points){
        double slope = point.slopeTo(p);
        if(slope != -std::numeric_limits<double>::infinity()){
            if(slopes.count(slope) == 1){
                slopes.at(slope).push_back(p);
            } else {
                vector<Point> v;
                v.push_back(p);
                slopes.insert(pair<double, vector<Point>>(slope, v));
                slopes.at(slope).push_back(point);
            }
        }
    }

}
