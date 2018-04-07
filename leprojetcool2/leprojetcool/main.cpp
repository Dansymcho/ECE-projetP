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
   std::vector<std::vector<int>> test;
   //int *esc =0 ;

   Menu m2;


    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    std::string SfichS;
    std::string SfichA;
    int u = 0;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC])
    {

//        m2.Menu2Update();
      //m2.menu1(menu);
      if(choix == 0)
        {
            choix = m2.menu1(menu);
            m2.choixmenu1(choix, &g,u);
        }


        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update(u);

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    }
    //�g.sauvegarde(SfichS,SfichA);
    main();


    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


