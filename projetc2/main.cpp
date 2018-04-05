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
   int choix = 0;
   int *esc =0 ;

   Menu m2;


    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    //g.make_example();




    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC])
    {

//        m2.Menu2Update();
      //m2.menu1(menu);
      if(choix == 0)
        {
            choix = m2.menu1(menu);
        m2.choixmenu1(choix, &g);
        }


        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    main();
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


