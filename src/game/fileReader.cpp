#include "../../headers/game/fileReader.h"
#include <fstream>

namespace fileReader {
    FileReader::FileReader(){
        save1 = "resources/save1";
        save2 = "resources/save2";
        save3 = "resources/save3";
        save4 = "resources/save4";
    }
    std::shared_ptr<canvas::Canvas> FileReader::loadTitleScreeen() {
        std::fstream title("resources/titlescreen.txt");
        int sizeX,sizeY;
        title >> sizeX >> sizeY;
        std::shared_ptr<canvas::Canvas> titlescreen(new canvas::Canvas(sizeX,sizeY," "));
        int lines,x,y;
        title >> lines >> x >> y;
        color::ForegroundColor fcolor(50,0,50);
        for (int i=0;i<lines;++i){
            int crx,cry;
            title>>crx>>cry;
            color::BackgroundColor color(150-crx,30,150-cry);
            titlescreen->changeDrawing(crx+x,cry+y,color.getString()+fcolor.getString()+"┼"+color::Color::reset);
        }
        int elements;
        title >> elements;
        for (int el=0; el<elements; ++el) {
            title >> lines >> x >> y;
            for (int i = 0; i<=lines; ++i) {
                std::string line;
                getline(title,line);
                for (int j=0; j<line.length();++j) {
                    titlescreen->changeDrawing(x+i,y+j,line.substr(j,1));
                }
            }
        }
        int length;
        title >> lines >> length >> x >> y;
        std::vector<int> reds = {140,152,142,164,137,125,133,150,152,149,130,127};
        std::vector<int> greens = {30,41,35,37,23,28,40,24,34,41,22,19};
        std::vector<int> greys = {160,165,120,125,80,85};
        color::ForegroundColor grey(10,10,10);
        for (int i = 0; i<lines; ++i) {
            for (int j=0; j<length;++j) {
                std::string line;
                title >> line;
                color::ForegroundColor bricks(reds[(i+j)%reds.size()],greens[(i+j)%greens.size()],0);
                color::ForegroundColor kitty(greys[(i+j*(i+4))%greys.size()],greys[(i+j*(i+4))%greys.size()],greys[(i+j*(i+4))%greys.size()]);
                if (line!=".") {
                    if (i>5) {
                        titlescreen->changeDrawing(x+i,y+j,bricks.getString()+line+color::ForegroundColor::reset);
                    } else {
                        titlescreen->changeDrawing(x+i,y+j,kitty.getString()+line+color::ForegroundColor::reset);
                    }
                }
            }
        }
        title.close();
        return titlescreen;
    }
}