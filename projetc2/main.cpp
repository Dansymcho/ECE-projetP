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

   Menu m2;


    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /*/// Un exemple de graphe
    Graph g;
    g.make_example();*/
    Graph g;
    //g.lectureFichier("sforet.txt");




    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {


        //Menu::creermenu2(m2);
        m2.Menu2Update();
      // m2.menu1(menu);


        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        //g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


