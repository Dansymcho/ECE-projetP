#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
   BITMAP *menu;

    menu = create_bitmap(SCREEN_W,SCREEN_H);
   menu = load_bitmap("pics/menu.bmp",NULL);

    int mn;
    if((mouse_b&1) && (mouse_x>300 && mouse_x<725))
    {

        if(mouse_y>105 && mouse_y<210)
        {
            mn=1;

            return mn;
        }


        if(mouse_y>280 && mouse_y<385)
        {
            mn=2;
            return mn;
        }
        if(mouse_y>440 && mouse_y<545)
            {
            mn=3;
            return mn;
        }
        ///pour quitter le jeu
        if(mouse_y>615 && mouse_y<720)
            exit(0);
    }

    switch(mn)
    {
    case 1:
        clear_bitmap(menu);

        Graph g;
        g.make_example();
    }

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();




    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
       blit(menu, grman::page, 0,0,0,0,SCREEN_W,SCREEN_H);
        blit(grman::page,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        //g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        //grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


