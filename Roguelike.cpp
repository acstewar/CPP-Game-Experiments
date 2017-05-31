#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Skill
{
    protected:
    SDL_Surface *icon;
    int cost;
    int type;//type of skill
    char name[16];
    int magnitude;//degree of effect
    //type
    public:
    Skill()
    {
    }
    Skill(int newcost, int newtype, char newname[16], int newmagnitude, SDL_Surface *lolicon)
    {
    cost = newcost;
    type = newtype;
    magnitude = newmagnitude;
    for(int i = 0;i<16;i++)
        {
        name[i] = newname[i];
        }
    icon = lolicon;
    }
    ~Skill()
    {
    }
    int getCost(){return cost;}
    int getType(){return type;}
    char getNameChar(int index){return name[index];}
    char* getName(){return name;};
    int getMagnitude(){return magnitude;}
    SDL_Surface* getIcon(){return icon;}
    void setIcon(SDL_Surface* newicon){icon = newicon;return;}
    void setCost(int newcost){cost = newcost;}
    void setType(int newType){type = newType;}
    void setMagnitude(int newmagnitude){magnitude = newmagnitude;}
};

class Weapon
{
    protected:
    SDL_Surface *icon;
    int attack;
    char name [16];
    public:
    Weapon()
    {
    }
    Weapon(int newattack, char newname[16])
    {
    attack = newattack;
    for(int i = 0;i < 16;i++)
        {
        name[i] = newname[i];
        }
    }
    ~Weapon()
    {
    }
    int getAttack(){return attack;}
    char getNameChar(int index){return name[index];}
    char* getName(){return name;};
    SDL_Surface* getIcon(){return icon;}
    void setIcon(SDL_Surface* newicon){icon = newicon;return;}
    void setAttack(int newattack){attack = newattack;return;}
};

class Armor
{
    protected:
    SDL_Surface *icon;
    int defense;
    char name[16];
    public:
    Armor()
    {
    }
    Armor(int newdefense, char newname[16])
    {
    defense = newdefense;
    for(int i = 0;i < 16;i++)
        {
        name[i] = newname[i];
        }
    }
    ~Armor()
    {
    }
    int getDefense(){return defense;}
    char getNameChar(int index){return name[index];}
    char* getName(){return name;}
    SDL_Surface* getIcon(){return icon;}
    void setIcon(SDL_Surface* newicon){icon = newicon;return;}
    void setDefense(int newdefense){defense = newdefense;return;}
};

class Character
{
    protected:
        int level;
        int exp;
        int hp;
        int maxhp;
        int mp;
        int maxmp;
        int strength;
        int endurance;
        int agility;
        int intelligence;
        Skill abilities[8];
        Weapon weapon;
        Armor armor;
        bool alive;
        bool offence;//Offensive buff
        bool defence;//Defensive buff
        char name[16];
        char status[16];
    public:
        Character(int newlevel, int newexp, int newhp, int newmaxhp, int newmp, int newmaxmp, int newstrength, int newendurance, int newagility, int newintelligence, Skill newabilities[8], Weapon newweapon, Armor newarmor, char newname[16])
        {
        level = newlevel;
        exp = newexp;
        hp = newhp;
        maxhp = newmaxhp;
        mp = newmp;
        maxmp = newmaxmp;
        strength = newstrength;
        endurance = newendurance;
        agility = newagility;
        intelligence = newintelligence;
        alive = true;
        for(int i = 0;i<8;i++)
            {
            abilities[i] = newabilities[i];
            }
        weapon = newweapon;
        armor = newarmor;
        for(int i = 0;i < 16;i++)
            {
            name[i] = newname[i];
            }
        status[0] = 'O';
        status[1] = 'K';
        status[2] = 'A';
        status[3] = 'Y';
        defence = false;
        offence = false;
        }
        Character()
        {
        }
        ~Character()
        {
        }

        void takedamage(int attack)
        {
        int damage = 0;
        if(defence)
            {
            endurance += (int)endurance * 0.33;
            }
        damage = attack*2 - (endurance + agility/2);
        if(damage < 1)
            {
            damage = 1;
            }
        hp -= damage;
        if(defence)
            {
            endurance -= (int)endurance * 0.33;
            }
        return;
        //Death condition?
        }

        void healing(int power)
        {
        int heal = 0;
        heal = power*2 + intelligence;
        if(heal < 1)
            {
            heal = 1;
            }
        hp += heal;
        if(hp > maxhp)
        {
            hp = maxhp;
        }
        return;
        }

        int getStrength(){return strength;}
        int getEndurance(){return endurance;}
        int getAgility(){return agility;}
        int getIntelligence(){return intelligence;}
        int getLevel(){return level;}
        int getExp(){return exp;}
        int getHP(){return hp;}
        int getMaxHP(){return maxhp;}
        int getMP(){return mp;}
        int getMaxMP(){return maxmp;}
        bool getAlive(){return alive;}
        bool getOffence(){return offence;}
        bool getDefence(){return defence;}
        char* getName(){return name;}
        char* getStatus(){return status;}
        Skill getAbility(int index){return abilities[index];}
        Skill* getAbilityAddr(int index){return &abilities[index];}
        void setStrength(int newstrength){strength = newstrength;}
        void setEndurance(int newendurance){endurance = newendurance;}
        void setAgility(int newagility){agility = newagility;}
        void setIntelligence(int newintelligence){intelligence = newintelligence;}
        void setLevel(int newlevel){level = newlevel;}
        void setExp(int newexp){exp = newexp;}
        void setHP(int newhp){hp = newhp;}
        void setMaxHP(int newmaxhp){maxhp = newmaxhp;}
        void setMP(int newmp){mp = newmp;}
        void setMaxMP(int newmaxmp){maxmp = newmaxmp;}
        void setAlive (bool newlife){alive = newlife;}
        void setAbility(Skill newskill, int index){abilities[index] = newskill;}
        void setOffence(bool newoffence){offence = newoffence;}
        void setDefence(bool newdefence){defence = newdefence;}

        void recover()
        {
        char newailment[16] = "OKAY";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }

        void poisoned()
        {
        char newailment[16] = "POISONED";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }

        void paralyzed()
        {
        char newailment[16] = "PARALYZED";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }

        void sleep()
        {
        char newailment[16] = "SLEEP";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }

        void charmed()
        {
        char newailment[16] = "CHARMED";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }

        void dead()
        {
        char newailment[16] = "DEAD";
        for(int i = 0;i<16;i++)
            {
            status[i] = newailment[i];
            }
        }
};

class Sprite
{
    protected:
        SDL_Surface* image;
        SDL_Rect rect;
        int frame;//Current frame
        int length;//Length of frame sequence
        int xframe;//X Size of frame
        int yframe;//Y Size of frame

    public:
        Sprite(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;//X Size of frame
        yframe = newyframe;//Y Size of frame
        }
        Sprite()
        {
        }
        ~Sprite()
        {
        }
        SDL_Surface* getImage(){return image;}
        SDL_Rect getRect(){return rect;}
        SDL_Rect* getRectAddr(){return &rect;}
        int getFrame(){return frame;}
        int getLength(){return length;}
        int getXframe(){return xframe;}
        int getYframe(){return yframe;}
        void setImage(SDL_Surface* newimage){image = newimage;return;}
        void setRect(SDL_Rect newrect){rect = newrect;return;}
        void setFrame(int newframe){frame = newframe;return;}
        void setLength(int newlength){length = newlength;return;}
        void setXframe(int newxframe){xframe = newxframe;return;}
        void setYframe(int newyframe){yframe = newyframe;return;}
};

class Environment: public Sprite
{
    protected:
        int x;
        int y;
        bool visible;
        bool solid;
        //Might want to create a tag or something for what kind this is.
    public:
        Environment(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx,int newy, bool newvisible, bool newsolid)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        visible = newvisible;
        solid = newsolid;
        }
        Environment()
        {
        }
        void Visible()//Compute visibility of the object
        {
        visible = true;
        }
        ~Environment()
        {
        }
        int getX(){return x;}
        int getY(){return y;}
        bool getVisible(){return visible;}
        bool getSolid(){return solid;}
        void setFrame(int newx){x = newx;}
        void setLength(int newy){y = newy;}
        void setVisible(bool newvisible){visible = newvisible;}
        void setSolid(bool newsolid){solid = newsolid;}
};

class Gridstep
{
    protected:
        int direction;
        int distance;
        int priority;
        bool visited;
    public:
        Gridstep()
        {
        }
        Gridstep(int newdirection, int newdistance, int newpriority, bool newvisited)
        {
        direction = newdirection;
        distance = newdistance;
        priority = newpriority;
        visited = newvisited;
        }
        ~Gridstep()
        {
        }
        int getDirection(){return direction;}
        int getDistance(){return distance;}
        int getPriority(){return priority;}
        bool getVisited(){return visited;}
        void setDirection(int newdirection){direction = newdirection;}
        void setDistance(int newdistance){distance = newdistance;}
        void setPriority(int newpriority){priority = newpriority;}
        void setVisited(bool newvisited){visited = newvisited;}
};

class Entity: public Sprite
{
    protected:
        //Coordinates on map screen
        int x;
        int y;
    public:
        Entity(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        }
        Entity()
        {
        }
        ~Entity()
        {
        }
        int getX(){return x;}//This causes a segfault, only when the AI local map is created.
        int getY(){return y;}
        void setX(int newx){x = newx;}
        void setY(int newy){y = newy;}
        void setFrame(int newx){x = newx;}
        void setLength(int newy){y = newy;}
};

class Pickup: public Entity
{
    public:
        void (*effect) (Character *);
        Pickup(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, void (*neweffect) (Character*))
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        effect = neweffect;
        }
        Pickup()
        {
        }
        ~Pickup()
        {
        }
};

class Mob: public Entity
{
    public:
        Mob(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        }
        Mob()
        {
        }
        ~Mob()
        {
        }

};

class Enemy: public Mob
{
    //TODO: Add more attributes as you find a need for them.
    protected:
        int hp;
        int strength;
        int endurance;
        int agility;
        int intelligence;
        char name[16];
    public:
        Enemy(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, int newhp, int newstrength, int newendurance, int newagility, int newintelligence, char newname[16])
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        hp = newhp;
        strength = newstrength;
        endurance = newendurance;
        agility = newagility;
        intelligence = newintelligence;
        for(int i = 0;i < 16;i++)
            {
            name[i] = newname[i];
            }
        }
        Enemy()
        {
        }
        ~Enemy()
        {
        }
        int ai(Environment gameboard[30][20], int playerx, int playery, Enemy *enemies[45],Pickup *goodies[45],int allyx[4],int allyy[4])
        {
        //we'll go rando for now
        bool canmove = true;
        int dir = rand()%4+1;
        //We're going to set the integer using our ai algorithm
        int magnitude = 0;
        int mindistance = 100000;
        int distance = 0;

        //Stopgap kind of dumb and also super aggressive ai
        //
        for(int i = 0;i<4;i++)
        {
            if(allyx[i] != -1 && allyy[i]!= -1)
            {
            distance = (abs(allyx[i] - x) + abs(allyy[i] - y));
            if(distance < mindistance )
                {
                mindistance = distance;
                if(allyy[i] < y && y > 0 && (y - allyy[i] > magnitude))//up
                    {
                    if(!gameboard[x][y-1].getSolid())
                        {
                        magnitude = y - allyy[i];
                        dir = 1;
                        }
                    }
                if(allyx[i] > x && x < 29 && (allyx[i] - x > magnitude))
                    {
                    if(!gameboard[x+1][y].getSolid())
                        {
                        magnitude = allyx[i] - x;
                        dir = 2;
                        }
                    }
                if(allyy[i] > y && y < 19 && (allyy[i] - y > magnitude))
                    {
                    if(!gameboard[x][y+1].getSolid())
                        {
                        magnitude = allyy[i] - y;
                        dir = 3;
                        }
                    }
                if(allyx[i] < x && x > 0 && (x - allyx[i] > magnitude))//left
                    {
                    if(!gameboard[x-1][y].getSolid())
                        {
                        magnitude = x - allyx[i];
                        dir = 4;
                        }
                    }
                }
            }
        }

        magnitude = 0;
        distance = (abs(playerx - x) + abs(playery - y));

        if(distance < mindistance)//Have a certain distance so the enemies aren't chasing before they could see.
        {
        mindistance = distance;
        if(playery < y && (y - playery > magnitude))
        {
            if(y > 0)
            {
                if(!gameboard[x][y-1].getSolid())
                {
                magnitude = y - playery;
                dir = 1;
                }
            }
        }
        if(playerx > x && (playerx - x > magnitude))
        {
            if(x < 29)
            {
                if(!gameboard[x+1][y].getSolid())
                {
                magnitude = playerx - x;
                dir = 2;
                }
            }
        }
        if(playery > y && (playery - y > magnitude))
        {
            if(y < 19)
            {
                if(!gameboard[x][y+1].getSolid())
                {
                magnitude = playery - y;
                dir = 3;
                }
            }
        }
        if(playerx < x && (x - playerx > magnitude))
        {
            if(x > 0)
            {
                if(!gameboard[x-1][y].getSolid())
                {
                magnitude = x - playerx;
                dir = 4;
                }
            }
        }
        }

        if(mindistance > 10)
        {
        dir = rand()%4 + 1;
        }

        //Gridstep's direction and also the values of iindex should now tell us
        //How would this cause map issues? I'm only getting the value of something!
        //int dir = rand()%4 + 1;//Random between north, south, west and east. To be replaced by AI code above
        switch(dir)
            {
            case 1: if(y > 0)
                    {
                        if(!gameboard[x][y-1].getSolid())
                        {
                        for(int i = 0;i < 45;i++)
                            {
                            if(enemies[i] != NULL)
                                {
                                if(this->getX() == enemies[i]->getX() && this->getY() == enemies[i]->getY()+1)
                                    {
                                    canmove = false;
                                    }
                                }
                            }
                        if(canmove)
                            {
                            return 1;
                            }
                        }
                    }
                break;
            case 2: if(x < 29)
                    {
                        if(!gameboard[x+1][y].getSolid())//For some reason enemies can move right into a wall.
                            {
                            for(int i = 0;i < 45;i++)
                                {
                                if(enemies[i] != NULL)
                                    {
                                    if(this->getX()+1 == enemies[i]->getX() && this->getY() == enemies[i]->getY())
                                        {
                                        canmove = false;
                                        }
                                    }
                                }
                            if(canmove)
                                {
                                return 2;
                                }
                            }
                    }
                break;
            case 3: if(y < 19)
                    {
                        if(!gameboard[x][y+1].getSolid())
                            {
                            for(int i = 0;i < 45;i++)
                                {
                                if(enemies[i] != NULL)
                                    {
                                    if(this->getX() == enemies[i]->getX() && this->getY() +1 == enemies[i]->getY())
                                        {
                                        canmove = false;
                                        }
                                    }
                                }
                            if(canmove)
                                {
                                return 3;
                                }
                            }
                    }
                break;
            case 4: if(x > 0)
                    {
                        if(!gameboard[x-1][y].getSolid())
                            {
                            for(int i = 0;i < 45;i++)
                                {
                                if(enemies[i] != NULL)
                                    {
                                    if(this->getX() == enemies[i]->getX()+1 && this->getY() == enemies[i]->getY())
                                        {
                                        canmove = false;
                                        }
                                    }
                                }
                            if(canmove)
                                {
                                return 4;
                                }
                            }
                    }
                break;//move west
            }
        //Compute which space you want to move into using a little bit of AI magic
        //If the space is free, move to it
        //If the space is occupied by a player or ally, carry out attack against them
        //If the space is occupied by a pickup, nothing happens
        return 0;
        }

        void takedamage(int attack, bool buff)
        {
        int damage = 0;
        if(buff)
        {
        attack += (int)(attack * 0.33);
        }
        damage = attack*2 - (endurance + agility/2);
        if(damage < 1)
            {
            damage = 1;
            }
        hp -= damage;
        return;
        }
        //TODO: Add AI behavior

        int getStrength(){return strength;}
        int getEndurance(){return endurance;}
        int getAgility(){return agility;}
        int getIntelligence(){return intelligence;}
        int getHP(){return hp;}
        char* getName(){return name;}
        void setStrength(int newstrength){strength = newstrength;}
        void setEndurance(int newendurance){endurance = newendurance;}
        void setAgility(int newagility){agility = newagility;}
        void setIntelligence(int newintelligence){intelligence = newintelligence;}
        void setHP(int newhp){hp = newhp;}
};

class Ally: public Mob//This classes' functions are causing segfaults whenever a getter is called from it. Something must be wrong here somehow, because the getters are working fine in other classes.
{
    //TODO: Add more attributes as you find a need for them.
    protected:
    Character identity;//Which character is this?
    int id; //integer identificaton for the character
    public:
        Ally(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, Character newidentity, int newid)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        identity = newidentity;
        id = newid;
        }
        Ally()
        {
        }
        ~Ally()
        {
        }
        void ai(Enemy *enemies[45], Environment gameboard[30][20],int playerx,int playery, Ally *allies[4])//AI and rejoin cause problems whenever a getter are called from them.
        {
        int dir = 0;
        dir = rand()%4 + 1;//Start dir off as random.

        int magnitude = 0;
        int distance = abs(playerx - x) + abs(playery - y);//This is supposeduly causing a mystery segfault? I can't see why that would happen.

        if(distance < 10)//Have a certain distance so the enemies aren't chasing before they could see.
        {
        if(playery < y && (y - playery > magnitude))
        {
            if(y > 0)
            {
                if(!gameboard[x][y-1].getSolid())
                {
                magnitude = y - playery;
                dir = 1;
                }
            }
        }
        if(playerx > x && (playerx - x > magnitude))
        {
            if(x < 29)
            {
                if(!gameboard[x+1][y].getSolid())
                {
                magnitude = playerx - x;
                dir = 2;
                }
            }
        }
        if(playery > y && (playery - y > magnitude))
        {
            if(y < 19)
            {
                if(!gameboard[x][y+1].getSolid())
                {
                magnitude = playery - y;
                dir = 3;
                }
            }
        }
        if(playerx < x && (x - playerx > magnitude))
        {
            if(x > 0)
            {
                if(!gameboard[x-1][y].getSolid())
                {
                magnitude = x - playerx;
                dir = 4;
                }
            }
        }
        }

        bool canmove = true;
        switch(dir)
            {
            case 1://north
                if(y > 1){
                    if(!gameboard[x][y-1].getSolid()){
                    for(int i = 0;i<45;i++){
                        if(enemies[i] != NULL){
                            if(x == enemies[i]->getX() && y == enemies[i]->getY()+1){
                                enemies[i]->takedamage(identity.getStrength(),identity.getOffence());
                                canmove = false;
                                }
                            }
                        }
                    for(int i = 0;i<4;i++)
                        {
                        if(allies[i]!= NULL)
                            {
                            if((x == allies[i]->getX() && y - 1 == allies[i]->getY()))
                            canmove = false;
                            }
                        }
                    if(canmove)
                        {
                        y -= 1;
                        rect.y -= 32;
                        }
                    }break;
                }
            case 2://east
                if(x < 29){
                    if(!gameboard[x+1][y].getSolid()){
                    for(int i = 0;i<45;i++){
                        if(enemies[i] != NULL){
                            if(x+1 == enemies[i]->getX() && y == enemies[i]->getY()){
                                enemies[i]->takedamage(identity.getStrength(),identity.getOffence());
                                canmove = false;
                                }
                            }
                        }
                    for(int i = 0;i<4;i++)
                        {
                        if(allies[i]!= NULL)
                            {
                            if((x+1 == allies[i]->getX() && y == allies[i]->getY()))
                            canmove = false;
                            }
                        }
                    if(canmove)
                        {
                        x += 1;
                        rect.x += 32;
                        }
                    }break;
                }
            case 3://south
                if(y < 19)
                {
                    if(!gameboard[x][y+1].getSolid())
                    {
                    for(int i = 0;i<45;i++){
                        if(enemies[i] != NULL){
                            if(x == enemies[i]->getX() && y + 1 == enemies[i]->getY()){
                                enemies[i]->takedamage(identity.getStrength(),identity.getOffence());
                                canmove = false;
                                }
                            }
                        }
                    for(int i = 0;i<4;i++)
                        {
                        if(allies[i]!= NULL)
                            {
                            if((x == allies[i]->getX() && y + 1 == allies[i]->getY()))
                            canmove = false;
                            }
                        }
                    if(canmove)
                        {
                        y += 1;
                        rect.y += 32;
                        }
                    }
                break;
                }
            case 4://west
                if(x > 1){
                    if(!gameboard[x-1][y].getSolid()){
                    for(int i = 0;i<45;i++){
                        if(enemies[i] != NULL){
                            if(x == enemies[i]->getX()+1 && y == enemies[i]->getY()){
                                enemies[i]->takedamage(identity.getStrength(),identity.getOffence());
                                canmove = false;
                                }
                            }
                        }
                    for(int i = 0;i<4;i++)
                        {
                        if(allies[i]!= NULL)
                            {
                            if((x - 1 == allies[i]->getX() && y == allies[i]->getY()))
                            canmove = false;
                            }
                        }
                    if(canmove)
                        {
                        x -= 1;
                        rect.x -= 32;
                        }
                    }
                }break;
            }
        return;
        }

        //TODO: Perform attack on enemy target if the enemy passed in isn't null.
        int getId(){return id;}
        void setId(int newid){id = newid;}
        Character* getIdentityAddr(){return &identity;}
        Character getIdentity(){return identity;}//This caused a segfault
};

class Player: public Entity
{
    //TODO: Add more attributes you may need.
    protected:
        Character party[5];
        bool present[5];
    public:
        Skill blankskill;
        Player(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, Character newparty[5], bool newpresent[5])
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        x = newx;
        y = newy;
        for(int i = 0;i<5;i++)
            {
            party[i] = newparty[i];
            }
        for(int i = 0;i<5;i++)
            {
            present[i] = newpresent[i];
            }
        Skill blankskill = Skill(0,0,"BLANKSKILL",0,newimage);
        }
        Player()
        {
        }
        ~Player()
        {
        }
        void mov(int direction, Environment destination, Enemy *enemies[45], Pickup *goodies[45], Ally *allies[4])
        {
        //TODO: Add cases for entities, enemies etc.
        if(!destination.getSolid())
        {
        int index = 0;
        bool attack = false;
        //TODO: Add cases for goodie collission, and allies.
        switch(direction)
            {
            case 1://north
                for(int i = 0;i<45;i++)
                {
                    if(enemies[i] != NULL )
                    {
                        if(enemies[i]->getX() == this->getX() && enemies[i]->getY() == this->getY()-1)
                        {
                        index = i;
                        attack = true;
                        }
                    }
                }
                if(attack == false)
                    {
                    y -= 1;
                    rect.y -= 32;
                    }
                break;
            case 2://east
                for(int i = 0;i<45;i++)
                {
                    if(enemies[i] != NULL )
                    {
                        if(enemies[i]->getX() == this->getX()+1 && enemies[i]->getY() == this->getY())
                        {
                        index = i;
                        attack = true;
                        }
                    }
                }
                if(attack == false)
                {
                x += 1;
                rect.x += 32;
                }
                break;
            case 3://south
                for(int i = 0;i<45;i++)
                {
                    if(enemies[i] != NULL )
                    {
                        if(enemies[i]->getX() == this->getX() && enemies[i]->getY() == this->getY()+1)
                        {
                        index = i;
                        attack = true;
                        }
                    }
                }
                if(attack == false)
                    {
                    y += 1;
                    rect.y += 32;
                    }
                break;
            case 4://west
                for(int i = 0;i<45;i++)
                {
                    if(enemies[i] != NULL )
                    {
                        if(enemies[i]->getX() == this->getX()-1 && enemies[i]->getY() == this->getY())
                        {
                        index = i;
                        attack = true;
                        }
                    }
                }
               if(attack == false)
                    {
                    x -= 1;
                    rect.x -= 32;
                    }
                if(attack == true)
                    {
                    for(int i = 0;i<5;i++)
                        {
                        if(party[i].getAlive())
                            {
                            enemies[index]->takedamage(party[i].getStrength(),party[i].getOffence());
                            }
                        }
                    }
                break;
            }
        if(attack == true)
            {
            for(int i = 0;i<5;i++)
                {
                if(party[i].getAlive())
                    {
                    enemies[index]->takedamage(party[i].getStrength(),party[i].getOffence());
                    }
                }
            }
        //TODO: Code to handle attack
        }
        return;
        //If the space is empty, move into it
        //If the space is obstructed, move does not carry out
        //If the space is occupied by enemy, carry out attack against the enemy
        //If the space is occupied by ally, merge with them and move to the square
        //If the space is occupied by a pickup, destroy the pickup and gain its effect
        }
        Character getParty(int i){return party[i];}
        Character* getPartyAddr(int i){return &party[i];}
        bool getPresent(int i){return present[i];}
        void setParty(int i, Character newchar){party[i] = newchar;}//Causes a segfault
        void setPresent(int i, bool newpresent){present[i] = newpresent;}
        //TODO: add functions for the player object
};

class Uielement: public Sprite
{
    public:

        //The effect of a Uielement button can be quite varied. Some might change the state, others use a skill or item, and some
        //void (*effect) (Character *);
        //void (*effectstate) (int*,int);
        //Skill (*effectskill) (int, int, Player*);
        bool states[10];
        Uielement(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,bool newstates [10]//,void (*neweffectstate) (int*,int),Skill(*neweffectskill)(int, int, Player*))
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        for(int i = 0;i < 10;i++)
            {
            states[i] = newstates[i];
            }
        }
        Uielement()
        {
        }
        ~Uielement()
        {
        }

        bool getState(int i){return states[i];}
};

class Button: public Uielement//May not end up wanting this object
{
    //TODO: Add a function pointer
    protected:
        int statechange;
        int skillindexi;
        int skillindexj;
    public:
        Button(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,bool newstates [10],int newstatechange, int newskillindexi, int newskillindexj)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        statechange = newstatechange;
        skillindexi = newskillindexi;
        skillindexj = newskillindexj;
        for(int i = 0;i < 10;i++)
            {
            states[i] = newstates[i];
            }

        }
        Button()
        {
        }
        ~Button()
        {
        }
};

class Text: public Uielement
{
    public:
        std::string content;
        Text(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,bool newstates [10], std::string newcontent)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        for(int i = 0;i < 10;i++)
            {
            states[i] = newstates[i];
            }
        content = newcontent;
        }
        Text()
        {
        }
        ~Text()
        {
        }
        void rendermessage()
        {
        //TODO: Add functionality to rendermessage
        return;
        }
};

class Bar: public Uielement
{
    protected:
        int amount;
        int limit;
    public:
        Bar(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,bool newstates [10])
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe = newxframe;
        yframe = newyframe;
        for(int i = 0;i < 10;i++)
            {
            states[i] = newstates[i];
            }
        }
        Bar()
        {
        }
        ~Bar()
        {
        }
        void renderbar()
        {
        //TODO: Add functionality to renderbar
        return;
        }
        int getAmount(){return amount;}
        int getLimit(){return limit;}
        void setAmount(int newamount){amount = newamount;}
        void setLimit(int newlimit){limit = newlimit;}
};
//Functions

void rejoin(Player *player, Ally *ally)
{
player->setParty(ally->getId(),ally->getIdentity());
player->setPresent(ally->getId(),true);
return;
}

//Optimized load function
//Having some issues with transparency.
SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = SDL_LoadBMP( filename.c_str() );
    SDL_Surface* optimizedImage = NULL;

    if (loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage);
        if( optimizedImage != NULL)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 255, 255, 255);
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }
    else
        {
        return loadedImage;//it may be returning this image specifically, IE there may be an issue with the optimized image.
        }
    return optimizedImage;
}

//Goodie effect functions

void blankeffect (Character *nomatter)
{
nomatter->takedamage(1);
return;
}
//Todo: Make some different functions for buttons and pickups.

//Button effect functions

void changestate(int *state, int newvalue)//Given the address of state and the value we want to set it to.
{
*state = newvalue;//Set state to the value passed in.
}

//We want a function to get an ability.
Skill *selectability(int i, int j,Player *player)
{
return player->getParty(i).getAbilityAddr(j);
}

void changeblank(int *state, int newvalue)
{
return;
}

Skill selectblank(int i, int j,Player *player)
{
return player->blankskill;
}

void enemymov(int dir,int playerx,int playery, Enemy *enemy, Player *player,Ally* characters[4])//used to belong to enemy, was changed over because we really needed the player object.
{
bool attack = false;
bool charattack = false;
int index = 0;//If you're attacking an ally, which one are you going after?
switch(dir)
    {
    case 1:
        for(int i = 0;i<4;i++)
        {
        if(characters[i] != NULL)
            {
            if(enemy->getX() == characters[i]->getX() && enemy->getY() == characters[i]->getY() + 1)
                {
                charattack = true;
                index = i;
                }
            }
        }
        if((!(enemy->getX() == playerx) || !(enemy->getY() == playery + 1)) && !charattack)
            {
            enemy->setY(enemy->getY() - 1);
            enemy->getRectAddr()->y -= 32;
            }
        else
            {
                if(!charattack)
                {
                attack = true;
                }
            }
        break;//move north
    case 2:
        for(int i = 0;i<4;i++)
        {
        if(characters[i] != NULL)
            {
            if(enemy->getX() == characters[i]->getX() - 1 && enemy->getY() == characters[i]->getY())
                {
                charattack = true;
                index = i;
                }
            }
        }
        if((!(enemy->getX() == playerx - 1) || !(enemy->getY() == playery)) && !charattack)
            {
            enemy->setX(enemy->getX() + 1);
            enemy->getRectAddr()->x += 32;
            }
        else
            {
                if(!charattack)
                {
                attack = true;
                }
            }
        break;//move east
    case 3:
        for(int i = 0;i<4;i++)
        {
        if(characters[i] != NULL)
            {
            if(enemy->getX() == characters[i]->getX() && enemy->getY() == characters[i]->getY()-1)
                {
                charattack = true;
                index = i;
                }
            }
        }
        if((!(enemy->getX() == playerx) || !(enemy->getY() == playery - 1)) && !charattack)
            {
            enemy->setY(enemy->getY() + 1);
            enemy->getRectAddr()->y += 32;
            }
        else
            {
                if(!charattack)
                {
                attack = true;
                }
            }
        break;//move south
    case 4:
        for(int i = 0;i<4;i++)
        {
        if(characters[i] != NULL)
            {
            if(enemy->getX() == characters[i]->getX() + 1 && enemy->getY() == characters[i]->getY())
                {
                charattack = true;
                index = i;
                }
            }
        }
        if((!(enemy->getX() == playerx + 1) || !(enemy->getY() == playery)) && !charattack)
            {
            enemy->setX(enemy->getX() - 1);
            enemy->getRectAddr()->x -= 32;
            }
        else
            {
                if(!charattack)
                {
                attack = true;
                }
            }
        break;//move west
    }

if(attack)
    {
    int target = (rand() % 5);
        while(player->getPartyAddr(target)->getAlive() == false || player->getPresent(target) == false)
        {
        target = (rand() % 5);
        }
    player->getPartyAddr(target)->takedamage(enemy->getStrength());
    }

if(charattack)
    {
    characters[index]->getIdentityAddr()->takedamage(enemy->getStrength());
    }
}

bool checkclick(int x, int y, SDL_Rect rectangle)
{
    if(x > rectangle.x && x < rectangle.x + rectangle.w && y > rectangle.y && y < rectangle.y + rectangle.h)
    {
        return true;
    }
    return false;
}


int main ( int argc, char** argv )
{
    std::ofstream myfile;
    myfile.open ("error.txt");
    myfile << "Started main.\n";

    void (*testgoodie)(Character *);
    testgoodie = &blankeffect;

    Environment gameboard[30][20];
    Pickup *goodies [45];
    Enemy *enemies [45];
    Ally *allies [4] = {NULL,NULL,NULL,NULL};
    Uielement *interface [150];

    Uint32 start = 0;//This is for timer.
    start = SDL_GetTicks();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    //Initialize TTF
    if( TTF_Init() < 0)
    {
        printf( "Unable to init TTF: %s\n", SDL_GetError() );
        return 1;
    }
    // Starlabel
    SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 1280x720 video: %s\n", SDL_GetError());
        return 1;
    }

//Load essential game images:

    SDL_Surface* ground = SDL_LoadBMP("Ground.bmp");
    SDL_Surface* wall = SDL_LoadBMP("Wall.bmp");
    SDL_Surface* ally = SDL_LoadBMP("Ally.bmp");
    SDL_Surface* sprite = SDL_LoadBMP("Sprite.bmp");
    SDL_Surface* enemy = SDL_LoadBMP("Enemy.bmp");
    SDL_Surface* goodie = SDL_LoadBMP("Goodie.bmp");
    SDL_Surface* tray = SDL_LoadBMP("Tray.bmp");
    SDL_Surface* pausemenu = SDL_LoadBMP("Pausemenu.bmp");
    SDL_Surface* exitbutton = SDL_LoadBMP("Exitbutton.bmp");
    SDL_Surface* exitgamebutton = SDL_LoadBMP("Exitgamebutton.bmp");
    SDL_Surface* loadgame = SDL_LoadBMP("Loadgame.bmp");
    SDL_Surface* options = SDL_LoadBMP("Options.bmp");
    SDL_Surface* weapon = SDL_LoadBMP("Weapon.bmp");
    SDL_Surface* armor = SDL_LoadBMP("Armor.bmp");
    SDL_Surface* playerbutton = SDL_LoadBMP("Playerbutton.bmp");
    SDL_Surface* diabox = SDL_LoadBMP("Diabox.bmp");

    int alpha = SDL_ALPHA_OPAQUE * 0.5;
    SDL_SetAlpha(diabox,SDL_SRCALPHA,alpha);
    SDL_Rect textrect;
    textrect.x = 32;
    textrect.y = 40;

    SDL_Rect diarect[6];
    SDL_Surface* dialogue;
    std::string diawords [6];
    for(int i = 0;i<6;i++)
    {
    diarect[i].x = 40;
    diarect[i].y = 48 + (i * 32);
    }



    //std::string ourname(player.getParty(state-3).getAbility(i-33).getName());
    //message = TTF_RenderText_Solid(font,ourname.c_str(), textColor);
    //dstrect.x = 1040;
    //dstrect.y = 160 + (48*(i-33));
    //interface[i] = new Uielement(message,dstrect,0,0,0,0,states);

    SDL_Rect dstrect;
    dstrect.x = 512;
    dstrect.y = 520;

    Skill emptyabilities[8];
    char dumbname[16] = "Anon";//Whoo, this chain of code let's me know how to name something using strings and char*'s!

    for(int i = 0;i<8;i++)
    {
    emptyabilities[i] = Skill(5,0,dumbname,5,armor);
    }

    char name[16] = "Cotton Sword";
    Weapon wepon = Weapon(0,name);
    char alias[16] = "Short Shirt";
    Armor armoire = Armor(0,alias);

    //Character(int newlevel, int newexp, int newhp, int newmaxhp, int newmp, int newmaxmp, int newstrength, int newendurance, int newagility, int newintelligence, Skill newabilities[8], Weapon newweapon, Armor newarmor)

    Character Auto = Character(1,0,10,10,10,10,5,5,5,5,emptyabilities,wepon,armoire,"AUTO");
    Character ALU = Character(1,0,10,10,10,10,5,5,5,5,emptyabilities,wepon,armoire,"ALU");
    Character Dragon = Character(1,0,10,10,10,10,5,5,5,5,emptyabilities,wepon,armoire,"DRAGON");
    Character Kitsun = Character(1,0,10,10,10,10,5,5,5,5,emptyabilities,wepon,armoire,"KITSUN");
    Character Lucid = Character(1,0,10,10,10,10,5,5,5,5,emptyabilities,wepon,armoire,"LUCID");

    Auto.setDefence(true);
    Auto.setOffence(true);

    Character group [5] = {Auto,ALU,Dragon,Kitsun,Lucid};
    bool groupthere[5] = {true,true,true,true,true};

    //Enemy(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, int newhp, int newstrength, int newendurance, int newagility, int newintelligence)
    //Character(int newlevel, int newexp, int newhp, int newmaxhp, int newmp, int newmaxmp, int newstrength, int newendurance, int newagility, int newintelligence, Skill newabilities[8], Weapon newweapon, Armor newarmor)

    Player player = Player(sprite,dstrect,0,0,0,0,15,15,group,groupthere);
    Environment tile = Environment();
    Environment barrier = Environment();

    for(int i = 0;i<30;i++)//Create empty map
    {
        for(int j = 0;j < 20;j++)
        {
        dstrect.x = 32 + i * 32;
        dstrect.y = 40 + j * 32;
        tile = Environment(ground, dstrect,0,0,0,0,i,j,true, false);
        gameboard[i][j] = tile;
        }
    }

    dstrect.y = 552;
    for(int i = 0;i<30;i++)
    {
        if(i != 21)
        {
        dstrect.x = 32+i*32;
        barrier = Environment(wall,dstrect,0,0,0,0,i,16,true,true);
        gameboard[i][16] = barrier;
        }
    }

    //char dumbname[16] = "Anon";//Whoo, this chain of code let's me know how to name something using strings and char*'s!
    dumbname[0] = 'E';
    dumbname[1] = 'N';
    dumbname[2] = 'E';
    dumbname[3] = 'M';
    dumbname[4] = 'Y';
    //Create some enemies
    dstrect.x = 32;
    dstrect.y = 40;
    enemies[0] = new Enemy(enemy,dstrect,0,0,0,0,0,0,20,5,5,5,5,dumbname);
    dstrect.x = 96;
    dstrect.y = 72;
    enemies[1] = new Enemy(enemy,dstrect,0,0,0,0,2,1,20,5,5,5,5,dumbname);
    dstrect.x = 192;
    dstrect.y = 136;
    enemies[2] = new Enemy(enemy,dstrect,0,0,0,0,5,3,20,5,5,5,5,dumbname);
    dstrect.x = 704;
    dstrect.y = 552;
    enemies[3] = new Enemy(enemy,dstrect,0,0,0,0,21,16,20,5,5,5,5,dumbname);

    dstrect.x = 736;//22
    dstrect.y = 424;//12
    allies[0] = new Ally(ally,dstrect,0,0,0,0,22,12,ALU,1);

    dstrect.x = 192;//5
    dstrect.y = 520;//15
    allies[1] = new Ally(ally,dstrect,0,0,0,0,5,15,Dragon,2);

    //Ally(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, Character newidentity)
    //enemies[0] = &nemesis;

    int gx;
    int gy;

    for(int i = 0;i<10;i++)//Create Goodies
    {
    gx = rand() % 30;
    gy = rand() % 20;
    if(!gameboard[gx][gy].getSolid())
        {
        dstrect.x = (gx+1) * 32;
        dstrect.y = 40 + (gy * 32);
        goodies[i] = new Pickup(goodie,dstrect,0,0,0,0,gx,gy,&blankeffect);//Some of these are coming up invisible.
        }
    }
    //Pickup(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newx, int newy, void (*neweffect) (Character*))

    int deathcount = 0;

    //Create UI
    //This is creating a runtime error.

    TTF_Font *font = NULL;
    SDL_Color textColor = {255,255,255};
    font = TTF_OpenFont( "5x5_pixel.ttf", 14);
    std::string msg = "AAAA";
    SDL_Surface* message;

    bool states[10];
    for(int i = 0;i<10;i++)
    {
    states[i] = true;
    }

    //msg = static_cast<std::ostringstream*>( &(std::ostringstream() << enemies[i]->getHP()) )->str();//Code to translate an int to a string.

    int state = 7;
    int reservestate = 7;

    //First 2: UI side trays

    dstrect.x = 1024;
    dstrect.y = 0;
    interface[0] = new Uielement(tray,dstrect,0,0,0,0,states);

    dstrect.x = 1136;
    dstrect.y = 0;
    interface[1] = new Uielement(tray,dstrect,0,0,0,0,states);

    //2-7, player buttons
    for(int i = 2;i<7;i++)
    {
    dstrect.x = 1136;
    dstrect.y = 135*(i-2);
    interface[i] = new Uielement(playerbutton,dstrect,0,0,0,0,states);
    }

    //7-11: Player names
    for(int i = 7;i<12;i++)
    {
    msg = player.getParty(i-7).getName();
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.x = 1150;
    dstrect.y = 30 + (135 *(i-7));
    interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
    }

    //12-16 player HP numbers
    dstrect.x = 1150;
    for(int i = 12; i<17 ;i++)
    {
    msg = "HP   " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(0).getHP()) )->str() + "  i  " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(0).getMaxHP()) )->str();
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.y = 70 + (i - 12)*135;
    interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
    }

    for(int i = 17; i<22 ;i++)
    {
    msg = "MP   " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(0).getMP()) )->str() + "  i  " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(0).getMaxMP()) )->str();
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.y = 90 + (i - 17)*135;
    interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
    }

    for(int i = 22; i<29 ;i++)
    {
    std::string ourname(player.getParty(i-22).getStatus());
    message = TTF_RenderText_Solid(font, ourname.c_str(), textColor);
    dstrect.y = 50 + (i - 22)*135;
    interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
    }

    //Individual menus: 8 skills (3 surfaces per), weapon and armor (3 surfaces per), for a total of 30 surfaces. Switch out elements via objects.
    //Leave some room for possible inventory spaces.

    msg = "Sword";
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.x = 1040;
    dstrect.y = 24;
    interface[27] = new Uielement(message,dstrect,0,0,0,0,states);

    msg = "Atk";
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.x = 1040;
    dstrect.y = 56;
    interface[28] = new Uielement(message,dstrect,0,0,0,0,states);

    //Icon for a weapon
    dstrect.x = 1102;
    dstrect.y = 16;
    interface[29] = new Uielement(weapon,dstrect,0,0,0,0,states);

    msg = "Shirt";
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.x = 1040;
    dstrect.y = 88;
    interface[30] = new Uielement(message,dstrect,0,0,0,0,states);

    msg = "Def";
    message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    dstrect.x = 1040;
    dstrect.y = 120;
    interface[31] = new Uielement(message,dstrect,0,0,0,0,states);

    //Icon for a piece of armor
    dstrect.x = 1102;
    dstrect.y = 80;
    interface[32] = new Uielement(armor,dstrect,0,0,0,0,states);

    //Skill loop: only appears in update step.
    for(int i = 33; i<41 ;i++)
    {
        //Something about this instantiation is causing a segfault. I suspect it occurs when there's no ability.
        if(state < 8 && state > 2) //(only needed for update)
        {
        std::string ourname(player.getParty(state-3).getAbility(i-33).getName());
        message = TTF_RenderText_Solid(font,ourname.c_str(), textColor);
        dstrect.x = 1040;
        dstrect.y = 160 + (48*(i-33));
        interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
        //Skill icon next

        dstrect.w = 32;
        dstrect.h = 32;
        dstrect.x = 1090;
        dstrect.y = 150 + (48*(i-33));
        interface[i+8] = new Button(player.getParty(state-3).getAbility(i-33).getIcon(),dstrect,0,0,0,0,states,0,i-33,state-3);
        //Button(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,int newstates [10], void (*neweffectstate) (int*,int),Skill(*neweffectskill)(int, int, Player*),int newstatechange, int newskillindexi, int newskillindexj)
        //interface[i+8] = new Uielement(weapon,dstrect,0,0,0,0,states);//This line is causing a segfault

        //cost: This is pulling out some dangerous garbage values!
        msg = static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(state-3).getAbility(i-33).getCost() ) )->str();//Code to translate an int to a string.
        message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
        dstrect.x = 1125;
        dstrect.y = 160 + (48*(i-33));
        interface[i+16] = new Uielement(message,dstrect,0,0,0,0,states);
        }
    }
    //The next interface should be 56:


    for(int i = 0;i<10;i++){states[i] = false;}
    states[2] = true;

    //Pause menu

    dstrect.x = 128;
    dstrect.y = 72;
    interface[145] = new Uielement(pausemenu,dstrect,0,0,0,0,states);

    dstrect.x = 256;
    dstrect.y = 152;
    interface[146] = new Uielement(exitbutton,dstrect,0,0,0,0,states);

    dstrect.y = 280;
    interface[147] = new Uielement(exitgamebutton,dstrect,0,0,0,0,states);

    dstrect.y = 408;
    interface[148] = new Uielement(loadgame,dstrect,0,0,0,0,states);

    dstrect.y = 536;
    interface[149] = new Uielement(options,dstrect,0,0,0,0,states);

    for(int i = 0;i<10;i++){states[i] = true;}

    //Pause menu

    //We'll likely want to pave over this next bit at some point.

    //myfile << "Initialized all variables.\n";
    //myfile << "Entering loop\n";

    Skill *cursorskill;//The current skill in the player's use.
    cursorskill = NULL;
    int skilluser = 0;

    int allyx[4];
    int allyy[4];

    int mousex = 0;
    int mousey = 0;

    int dir = 0;//Direction enemy will move in
    bool playerturn = true;//Start on player's turn.
    bool done = false;
    while (!done)//Main game loop
    {
        //Set the message values here.
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))//Event loop
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if(event.key.keysym.sym == SDLK_k)
                        {
                        done = true;
                        break;
                        }
                    if (event.key.keysym.sym == SDLK_ESCAPE)//Change this to be a pause menu.
                        {
                            if(state != 2)
                            {
                            reservestate = state;
                            state = 2;
                            }
                            else
                            {
                            state = reservestate;
                            }
                        //done = true;
                        //break;
                        }

//for(int i = 1;i<6;i++)
//{
//diawords[i-1] = diaword[i];
//}
//diawords[5] = newmessage;
//

                    if (event.key.keysym.sym == SDLK_UP && playerturn && state != 2)
                        {
                        if(player.getY() > 0){player.mov(1,gameboard[player.getX()][player.getY()-1],enemies,goodies,allies);}
                        playerturn = false;
                        }
                    if (event.key.keysym.sym == SDLK_RIGHT && playerturn && state != 2)
                        {
                        if(player.getX() < 29){player.mov(2,gameboard[player.getX()+1][player.getY()],enemies,goodies,allies);}
                        playerturn = false;
                        }
                    if (event.key.keysym.sym == SDLK_DOWN && playerturn && state != 2)
                        {
                        if(player.getY() < 19){player.mov(3,gameboard[player.getX()][player.getY()+1],enemies,goodies,allies);}
                        playerturn = false;
                        }
                    if (event.key.keysym.sym == SDLK_LEFT && playerturn && state != 2)
                        {
                        if(player.getX() > 0){player.mov(4,gameboard[player.getX()-1][player.getY()],enemies,goodies,allies);}
                        playerturn = false;
                        }
                    //if(event.key.keysym.sym == SDLK_SPACE)
                        //{                        break;
                        //}

        for(int i = 0;i<6;i++)
            {
            if(player.getY() < 8)
                {
                textrect.y = 488;
                for(int i = 0;i<6;i++)
                    {
                    diarect[i].y = 496 + (i*32);
                    }
                }
            if(player.getY() > 11)
                {
                textrect.y = 40;
                for(int i = 0;i<6;i++)
                    {
                    diarect[i].y = 48 + (i*32);
                    }
                }
            }

            //Mouse event: will be used to check for player button presses that might take up a turn, like casting a spell, using an item, etc.
            case SDL_MOUSEMOTION:
                {
                    mousex = event.motion.x;
                    mousey = event.motion.y;
                    //Later: check for over.
                    //Set mouse x and y.
                    break;
                }

            case SDL_MOUSEBUTTONDOWN:
                {
                if(event.button.button == SDL_BUTTON_RIGHT )
                    {
                        if(state != 2)//Gets rid of an unwanted cursorskill.
                        {
                        cursorskill = NULL;
                        interface[124] = NULL;
                        }
                    break;
                    }
                if(event.button.button == SDL_BUTTON_LEFT )
                    {
                        //Skill Buttons
                        for(int i = 41;i<49;i++)
                        {
                            if(cursorskill == NULL && interface[i]!= NULL && state > 2 && state < 8)
                            {
                                if(checkclick(mousex,mousey,interface[i]->getRect()) && state != 2)
                                {
                                skilluser = state - 3;
                                cursorskill = selectability(state - 3,i - 41,&player);
                                dstrect.x = 50;
                                dstrect.y = 50;
                                interface[124] = new Uielement(cursorskill->getIcon(),dstrect,0,0,0,0,states);
                                }
                            }
                        }
                        //Player buttons
                        for(int i = 2;i<7;i++)
                        {
                            if(interface[i] != NULL && cursorskill == NULL)
                            {
                                if(checkclick(mousex,mousey,interface[i]->getRect()) && state != 2)
                                {
                                state = i+1;
                                }
                            }
                            if(interface[i] != NULL && cursorskill != NULL)
                            {
                                if(checkclick(mousex,mousey,interface[i]->getRect()) && state != 2)
                                {
                                    if(cursorskill->getCost() <= player.getParty(skilluser).getMP())//Todo: add feedback for insufficient skill
                                    {
                                        if(cursorskill->getType() == 2)
                                        {
                                        player.getPartyAddr(i-2)->healing(player.getParty(i-2).getIntelligence());
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        //Healing
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 3)
                                        {
                                        //Defence Buff
                                        player.getPartyAddr(i-2)->setDefence(true);
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 4)
                                        {
                                        //Offence Buff
                                        player.getPartyAddr(i-2)->setOffence(true);
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 5)
                                        {
                                        //Ailment healing
                                        player.getPartyAddr(i-2)->recover();
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }
                                    }
                                //If the type is 1, this can happen
                                //Perform the function of the ability.

                                }
                            }
                        }

                        //Enemies treated as Buttons
                        for(int i = 0;i<45;i++)
                        {
                            if(cursorskill != NULL && enemies[i] != NULL)
                            {
                                if(checkclick(mousex,mousey,enemies[i]->getRect()) && state != 2)
                                {
                                    if(cursorskill->getType() == 1)
                                    {
                                    enemies[i]->takedamage(player.getParty(skilluser).getIntelligence() + 2*cursorskill->getMagnitude(),false);
                                    player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                    cursorskill = NULL;
                                    interface[124] = NULL;
                                    playerturn = false;
                                    }
                                //If the type is 1, this can happen
                                //Perform the function of the ability.
                                }
                            }
                        }

                        //Allies treated as buttons
                        for(int i = 0;i<5;i++)
                        {
                            if(cursorskill != NULL && allies[i] != NULL)
                            {
                                if(checkclick(mousex,mousey,allies[i]->getRect()) && state != 2)
                                {
                                    if(cursorskill->getCost() <= player.getParty(skilluser).getMP())//Todo: add feedback for insufficient skill
                                    {
                                        if(cursorskill->getType() == 2)
                                        {
                                        player.getPartyAddr(i-2)->healing(player.getParty(i-2).getIntelligence());
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        //Healing
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 3)
                                        {
                                        //Defence Buff
                                        player.getPartyAddr(i-2)->setDefence(true);
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 4)
                                        {
                                        //Offence Buff
                                        player.getPartyAddr(i-2)->setOffence(true);
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }

                                        if(cursorskill->getType() == 5)
                                        {
                                        //Ailment healing
                                        player.getPartyAddr(i-2)->recover();
                                        player.getPartyAddr(skilluser)->setMP(player.getParty(skilluser).getMP() - cursorskill->getCost());
                                        cursorskill = NULL;
                                        interface[124] = NULL;
                                        playerturn = false;
                                        }
                                    }
                                }
                            }
                        }

                        //Exit to menu
                        if(interface[147]!= NULL && state == 2)//Exit to desktop
                        {
                            if(checkclick(mousex,mousey,interface[147]->getRect()))
                            {
                            done = true;
                            }
                        }
                        //Load Game Menu
                        //Options Menu

                        break;
                    }
                }
                // end switch
            } // end of message processing DRAWING STARTS HERE
        }
        if(!playerturn)//If player turn over
        {
            //Ally Move, check for merge.
            for(int i = 0;i<4;i++)
            {
                if(allies[i]!=NULL)
                {
                if(allies[i]->getX() == player.getX() && allies[i]->getY() == player.getY())//check merge first
                    {
                    rejoin(&player,allies[i]);
                    delete allies[i];
                    allies[i] = NULL;
                    }
                if(allies[i]!=NULL)
                {
                    allies[i]->ai(enemies,gameboard,player.getX(),player.getY(),allies);//Do a move
                    if(allies[i]->getX() == player.getX() && allies[i]->getY() == player.getY())//check merge next
                    {
                    rejoin(&player,allies[i]);
                    delete allies[i];
                    allies[i] = NULL;
                    }
                }

                }
            }
            for(int i = 0;i<4;i++)
            {
                if(allies[i] != NULL)
                {
                allyx[i] = allies[i]->getX();
                allyy[i] = allies[i]->getY();
                }
                else
                {
                allyx[i] = -1;
                allyy[i] = -1;
                }
            }
            //Enemy AI
            for(int i = 0;i<45;i++)
            {
                if(enemies[i] != NULL)
                {
                dir = enemies[i]->ai(gameboard,player.getX(),player.getY(),enemies,goodies,allyx,allyy);
                enemymov(dir,player.getX(),player.getY(),enemies[i],&player,allies);
                }
            }

//Check for goodies

            for(int i = 0;i<45;i++)
            {
                if(goodies[i] != NULL)
                {
                    if((goodies[i]->getX() == player.getX()) && (goodies[i]->getY() == player.getY()))
                    {
                    //find way to determine which party member to effect with goodie, may want to change goodie function template.
                    goodies[i]->effect(player.getPartyAddr(0));
                    //Activate goodie's effect.
                    delete goodies[i];
                    goodies[i] = NULL;
                    }
                }
            }

//Check Enemy death
            for(int i = 0;i<45;i++)
            {
            if(enemies[i]!= NULL)
                {
                if(enemies[i]->getHP() <= 0)
                    {
                    delete enemies[i];
                    enemies[i] = NULL;
                    }
                }
            }
        //Check Player death
            for(int i = 0;i<5;i++)
            {
            if(player.getPartyAddr(i)->getHP() <= 0)
                {
                player.getPartyAddr(i)->setHP(0);
                player.getPartyAddr(i)->dead();
                player.getPartyAddr(i)->setAlive(false);
                }
            if(player.getPartyAddr(i)->getHP() > player.getPartyAddr(i)->getMaxHP())
                {
                player.getPartyAddr(i)->setHP(player.getPartyAddr(i)->getMaxHP());
                }
            }

        //Check Ally death
            for(int i = 0;i<4;i++)
            {
                if(allies[i]!=NULL)
                {
                if(allies[i]->getIdentityAddr()->getHP() <= 0)
                    {
                    //Just destroy it for now
                    delete allies[i];
                    allies[i] = NULL;
                    }
                }
            }

        //Check game over
            deathcount = 0;
            for(int i = 0;i<5;i++)
            {
                if(!player.getPartyAddr(i)->getAlive() || !player.getPresent(i))
                {
                deathcount += 1;
                }
            }

            if(deathcount == 5)
            {
            done = true;
            }

            playerturn = true;
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));//Clear screen to black
        //button1message = TTF_RenderText_Solid(font, buttontext1, textColor );

        for(int i = 0;i < 30;i++)//Draw gameboard
        {
            for(int j = 0;j < 20;j++)
            {
            if(gameboard[i][j].getVisible())
                {
                SDL_BlitSurface(gameboard[i][j].getImage(),0,screen,gameboard[i][j].getRectAddr());
                }
            }
        }

        //Draw goodie objects
        for(int i = 0;i<45;i++)
        {
            if(goodies[i] != NULL)
            {
            SDL_BlitSurface(goodies[i]->getImage(),0,screen,goodies[i]->getRectAddr());
            }
        }

        for(int i = 0;i<4;i++)
        {
            if(allies[i] != NULL)
            {
            SDL_BlitSurface(allies[i]->getImage(),0,screen,allies[i]->getRectAddr());//caused a segfault, so we changed it for now.
            }
        }
        //Draw Ally objects

        for(int i = 0;i < 45;i++)//Draw enemy objects
        {
            //Add an if statement here.
            if(enemies[i] != NULL)
            {
            SDL_BlitSurface(enemies[i]->getImage(),0,screen,enemies[i]->getRectAddr());//Remember, use pointer->function to call a function on a object pointer array value.
            }
        }

        SDL_BlitSurface(player.getImage(),0,screen,player.getRectAddr());//draw player object

        SDL_BlitSurface(diabox,0,screen,&textrect);
        for(int i = 0;i<6;i++)
        {
        diawords[i] = "AAAA";
        dialogue = TTF_RenderText_Solid(font,diawords[i].c_str(),textColor);
        SDL_BlitSurface(dialogue,0,screen,&diarect[i]);//draw player object
        }
        //Draw the diabox


//Update message:


        //Update parts of the UI
        dstrect.x = 1150;
        for(int i = 12; i<17 ;i++)//Update HP amount
        {
        msg = "HP   " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(i-12).getHP()) )->str() + "  i  " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(i-12).getMaxHP()) )->str();
        message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
        dstrect.y = 70 + (i - 12)*135;
        interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
        }

        for(int i = 17; i<22 ;i++)//Update max HP
        {
        msg = "MP   " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(i-17).getMP()) )->str() + "  i  " + static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(i-17).getMaxMP()) )->str();
        message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
        dstrect.y = 90 + (i - 17)*135;
        interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
        }

        for(int i = 22; i<29 ;i++)//update ailment status
        {
        //player.getPartyAddr(i-17)->sleep();Ailments have to be set through pointers!!
        std::string ourname(player.getParty(i-22).getStatus());
        dstrect.y = 50 + (i - 22)*135;
        message = TTF_RenderText_Solid(font,ourname.c_str(), textColor);
        interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
        }

        for(int i = 33; i<41 ;i++)//Update Secondary Tray: let's move this somewhere where it will only be triggered by mouse updates.
        {
            //Something about this instantiation is causing a segfault. I suspect it occurs when there's no ability.
            if(state < 8 && state > 2) //(only needed for update)
            {
            std::string ourname(player.getParty(state-3).getAbility(i-33).getName());
            message = TTF_RenderText_Solid(font,ourname.c_str(), textColor);
            dstrect.x = 1040;
            dstrect.y = 160 + (48*(i-33));
            interface[i] = new Uielement(message,dstrect,0,0,0,0,states);
            //Skill icon next

            dstrect.w = 32;
            dstrect.h = 32;
            dstrect.x = 1090;
            dstrect.y = 150 + (48*(i-33));
            interface[i+8] = new Button(player.getParty(state-3).getAbility(i-33).getIcon(),dstrect,0,0,0,0,states,0,i-33,state-3);
            //Button(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe,bool newstates [10], void (*neweffectstate) (int*,int),Skill(*neweffectskill)(int, int, Player*),int newstatechange, int newskillindexi, int newskillindexj)
            msg = static_cast<std::ostringstream*>( &(std::ostringstream() << player.getParty(state-3).getAbility(i-33).getCost() ) )->str();//Code to translate an int to a string.
            message = TTF_RenderText_Solid(font, msg.c_str(), textColor);
            dstrect.x = 1125;
            dstrect.y = 160 + (48*(i-33));
            interface[i+16] = new Uielement(message,dstrect,0,0,0,0,states);
            }
        }

        //Draw the UI
        for(int i = 0;i<150;i++)
        {
            if(interface[i] != NULL)
            {
                if(interface[i]->getState(state))
                {
                SDL_BlitSurface(interface[i]->getImage(),0,screen,interface[i]->getRectAddr());//We're getting a segfault caused by trying to blit the UI.
                }
            }
        }


        SDL_Flip(screen);
    } // end main loop
    }

    //free your memory

    TTF_CloseFont(font);
    SDL_FreeSurface(ground);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(enemy);
    SDL_FreeSurface(ally);
    SDL_FreeSurface(tray);
    SDL_FreeSurface(pausemenu);
    SDL_FreeSurface(exitbutton);
    SDL_FreeSurface(exitgamebutton);
    SDL_FreeSurface(loadgame);
    SDL_FreeSurface(options);
    SDL_FreeSurface(playerbutton);
    SDL_FreeSurface(diabox);

    //SDL_FreeSurface(goodie);
    atexit(SDL_Quit);//This used to be at starlabelf

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

//Old code below


