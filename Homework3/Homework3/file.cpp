#include <iostream>
#include <string>
using namespace std;

//Declaration of the abstract class
class File
{
public:
    File(string nm);
    virtual ~File() {};
    string name() const;
    virtual void open() const = 0;
    //open() is a pure virtual function
    virtual void redisplay() const;
    //redisplay() is a non-pure virtual function since for TextMsg and Picture, it does the same thing

private:
    string m_name;
};

File::File(string nm)
:m_name(nm)
{}

string File::name() const
{
    return m_name;
}

void File::redisplay() const
{
    cout << "refresh the screen";
}

//Declaration of derived class: TextMsg
class TextMsg : public File
{
public:
    TextMsg(string nm);
    virtual ~TextMsg();
    virtual void open() const;
};

TextMsg::TextMsg(string nm)
:File(nm)
{}

TextMsg::~TextMsg()
{
    cout << "Destroying " << name() << ", a text message" << endl;
}

void TextMsg::open() const
{
    cout << "open text message";
}

//Declaration of derived class: Video
class Video : public File
{
public:
    Video(string nm, int time);
    virtual ~Video();
    virtual void open() const;
    virtual void redisplay() const;
private:
    int m_time;
};

Video::Video(string nm, int time)
:File(nm), m_time(time)
{}

Video::~Video()
{
    cout << "Destroying" << name() <<", a video" << endl;
}

void Video::open() const
{
    cout << "play " << m_time << " second video";
}

void Video::redisplay() const
{
    cout << "replay video";
}

//Declaration of derived class: Picture
class Picture : public File
{
public:
    Picture(string nm);
    virtual ~Picture();
    virtual void open() const;
};

Picture::Picture(string nm)
:File(nm)
{}

Picture::~Picture()
{
    cout << "Destroying the picture " << name() << endl;
}

void Picture::open() const
{
    cout << "show picture";
}

void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}

int main()
{
    File* files[4];
    files[0] = new TextMsg("fromFred.txt");
    // Videos have a name and running time
    files[1] = new Video("kitty.mpg", 57);
    files[2] = new Picture("poster.jpg");
    files[3] = new Picture("still.jpg");
    
    for (int k = 0; k < 4; k++)
        openAndRedisplay(files[k]);
    
    // Clean up the files before exiting
    cout << "Cleaning up" << endl;
    for (int n = 0; n < 4; n++)
        delete files[n];
}