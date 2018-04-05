#include "graph.h"


/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    /// La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    /// Le slider de réglage de valeur des sommets
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 50.0); /// Valeurs des sliders.
    m_slider_value.set_dim(20,80); /// taille du slider
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    /// Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    /// Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    /// Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12); ///taille du slider aretes
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    /// Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    /// Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(20,60); ///taille de la boite des sliders aretes
    m_box_edge.set_bg_color(BLANCJAUNE);

    /// Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); /// Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40); ///taille du bouton slider aretes
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    /// Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_menu2);
    ///boite du menu2
    m_menu2.set_frame(700, 420, 200, 180);
    m_menu2.set_bg_color(GRISCLAIR);
    m_menu2.set_moveable();

    ///boite titre
    m_menu2.add_child( m_titre );
    m_titre.set_dim(180, 20);
    m_titre.set_gravity_y( grman::GravityY::Up );


    ///message : sous-menu
    m_titre.add_child( m_ssmenu );
    m_ssmenu.set_message("SOUS-MENU");
    m_ssmenu.set_gravity_y(grman::GravityY::Up );


    ///bouton ajout
    m_menu2.add_child( m_bnouveau );
    m_bnouveau.set_frame(12,40,180,30);
    m_bnouveau.set_bg_color(BLEU);

    ///message ajout
    m_bnouveau.add_child(m_nouveau);
    m_nouveau.set_message("Nouvelle espèce");

    ///boite enlever
    m_menu2.add_child( m_benlever );
    m_benlever.set_frame(12,80,180,30);
    m_benlever.set_bg_color(BLEU);

    ///messge enlever
    m_benlever.add_child(m_enlever);
    m_enlever.set_message("Annuler espèce");

    ///boite retour
    m_menu2.add_child( m_bretour );
    m_bretour.set_frame(12,120,180,30);
    m_bretour.set_bg_color(BLEU);

    ///message retour
    m_bretour.add_child(m_retour);
    m_retour.set_message("Retour au menu");

}




/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);


    ///infos graphe 1 à mettre sous forme de matrice ponderee

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...

    ///mer
   /* add_interfaced_vertex(0, 30.0, 450, 400, "elephantmers.jpg");
    add_interfaced_vertex(1, 60.0, 100, 400, "krill.jpg");
    add_interfaced_vertex(2,  50.0, 100, 100, "baleinebosse.jpg");
    add_interfaced_vertex(3,  0.0, 150, 250, "gorfou.jpg");
    add_interfaced_vertex(4,  100.0, 200, 400, "poissonsp.jpg");
    add_interfaced_vertex(5,  0.0, 250, 250, "poissonsg.jpg");
    add_interfaced_vertex(6,  0.0, 200, 100, "manchotadelie.jpg" );
    add_interfaced_vertex(7,  0.0, 300, 100, "leopardmers.jpg" );
    add_interfaced_vertex(8,  0.0, 325, 250, "manchotempereur.jpg");
    add_interfaced_vertex(9,  0.0, 350, 400, "phoqueweddell.jpg");
    add_interfaced_vertex(10,  0.0, 450, 100, "orque.jpg");

    add_interfaced_edge(1, 10, 0, 50.0);
    add_interfaced_edge(2, 10, 8, 75.0);
    add_interfaced_edge(3, 10, 9, 25.0);
    add_interfaced_edge(4, 7, 3, 25.0);
    add_interfaced_edge(5, 7, 6, 25.0);
    add_interfaced_edge(6, 7, 5, 0.0);
    add_interfaced_edge(7, 0, 5, 100.0);
    add_interfaced_edge(8, 9, 4, 20.0);
    add_interfaced_edge(9, 8, 4, 80.0);
    add_interfaced_edge(10, 8, 5, 80.0);
    add_interfaced_edge(11, 5, 4, 80.0);
    add_interfaced_edge(12, 6, 4, 80.0);
    add_interfaced_edge(13, 3, 4, 80.0);
    add_interfaced_edge(14, 4, 1, 80.0);
    add_interfaced_edge(15, 2, 1, 80.0);*/


    ///test
    /*add_interfaced_vertex(0, 30.0, 450, 400, "elephantmers.jpg");
    add_interfaced_vertex(1, 60.0, 100, 400, "krill.jpg");
    add_interfaced_vertex(2,  50.0, 100, 100, "baleinebosse.jpg");

    add_interfaced_edge(0, 0, 1, 50.0);
    add_interfaced_edge(1, 0, 2, 50.0);
    add_interfaced_edge(2, 1, 2, 75.0);*/



   ///foret
     add_interfaced_vertex(0, 30.0, 350, 150, "vegetal.jpg");
    add_interfaced_vertex(1, 60.0, 550, 150, "fourmi.jpg");
    add_interfaced_vertex(2,  50.0, 175, 150, "campagnol.jpg");
     add_interfaced_vertex(3, 30.0, 650, 325, "ecureuil.jpg");
    add_interfaced_vertex(4, 60.0, 475, 325, "chevreuil.jpg");
    add_interfaced_vertex(5,  50.0, 300, 325, "sanglier.jpg");
     add_interfaced_vertex(6, 30.0, 175, 325, "cerf.jpg");
    add_interfaced_vertex(7, 60.0, 550, 500, "chouette.jpg");
    add_interfaced_vertex(8,  50.0, 175, 500, "renard.jpg");
     add_interfaced_vertex(9, 30.0, 350, 500, "loup.jpg");

     add_interfaced_edge(0, 1, 0, 50.0);
    add_interfaced_edge(1, 9, 6, 50.0);
    add_interfaced_edge(2, 9, 5, 75.0);
    add_interfaced_edge(3, 9, 4, 50.0);
    add_interfaced_edge(4, 8, 4, 50.0);
    add_interfaced_edge(5, 8, 3, 75.0);
    add_interfaced_edge(6, 8, 2, 50.0);
    add_interfaced_edge(7, 7, 3, 50.0);
    add_interfaced_edge(8, 7, 2, 75.0);
    add_interfaced_edge(9, 6, 0, 50.0);
    add_interfaced_edge(10, 5, 0, 50.0);
    add_interfaced_edge(11, 4, 0, 75.0);
    add_interfaced_edge(12, 9, 3, 50.0);
    add_interfaced_edge(13, 3, 0, 50.0);
    add_interfaced_edge(14, 2, 0, 75.0);


    ///jungle

   /* add_interfaced_vertex(0, 30.0, 400, 450, "vegetaljungle.jpg");
    add_interfaced_vertex(1, 60.0, 100, 450, "hippo.jpg");
    add_interfaced_vertex(2,  50.0, 650, 450, "elephant.jpg");
     add_interfaced_vertex(3, 30.0, 325, 350, "fourmi.jpg");
    add_interfaced_vertex(4, 60.0, 500, 350, "babouin.jpg");
    add_interfaced_vertex(5,  50.0, 400, 200, "phaco.jpg");
     add_interfaced_vertex(6, 30.0, 100, 200, "buffle.jpg");
     add_interfaced_vertex(7, 30.0, 250, 200, "gnou.jpg");
    add_interfaced_vertex(8, 60.0, 550, 200, "zebre.jpg");
    add_interfaced_vertex(9,  50.0, 750, 200, "gazelle.jpg");
     add_interfaced_vertex(10, 30.0, 175, 50, "lion.jpg");
    add_interfaced_vertex(11, 60.0, 325, 50, "leopard.jpg");
    add_interfaced_vertex(12,  50.0, 500, 50, "guepard.jpg");
     add_interfaced_vertex(13, 30.0, 650, 50, "hyene.jpg");


    add_interfaced_edge(0, 13, 9, 50.0);
    add_interfaced_edge(1, 13, 5, 50.0);
    add_interfaced_edge(2, 12, 9, 75.0);
    add_interfaced_edge(3, 12, 5, 50.0);
    add_interfaced_edge(4, 11, 5, 50.0);
    add_interfaced_edge(5, 11, 7, 75.0);
    add_interfaced_edge(6, 10, 6, 50.0);
    add_interfaced_edge(7, 10, 7, 50.0);
    add_interfaced_edge(8, 10, 5, 75.0);
    add_interfaced_edge(9, 10, 8, 50.0);
    add_interfaced_edge(10, 10, 9, 50.0);
    add_interfaced_edge(11, 9, 0, 75.0);
    add_interfaced_edge(12, 8, 3, 50.0);
    add_interfaced_edge(13, 7, 0, 50.0);
    add_interfaced_edge(14, 6, 0, 75.0);
    add_interfaced_edge(15, 5, 0, 75.0);
    add_interfaced_edge(16, 4, 0, 75.0);
    add_interfaced_edge(17, 3, 0, 75.0);
    add_interfaced_edge(18, 2, 0, 75.0);
    add_interfaced_edge(19, 1, 0, 75.0);*/





}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

        // m_menu2.update();

   if ( m_interface->m_bnouveau.clicked() )
    {
        std::cout << "Nouvelle espèce" << std::endl;
    }

     if ( m_interface->m_benlever.clicked() )
    {
        std::cout << "Annuler espèce" << std::endl;
    }

     if ( m_interface->m_bretour.clicked() )
    {
        std::cout << "retour au menu" << std::endl;





    }

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
}



/***************************************************
                    Menu
****************************************************/


int Menu::menu1(BITMAP *menu)
{
    blit(menu, grman::page, 0,0,0,0,SCREEN_W,SCREEN_H);
    blit(grman::page,screen, 0,0,0,0,SCREEN_W,SCREEN_H);

    int mn;
    if((mouse_b&1) && (mouse_x>230 && mouse_x<570))
    {

        if(mouse_y>80 && mouse_y<165)
        {
            mn=1;


            return mn;
        }


        if(mouse_y>215 && mouse_y<300)
        {
            mn=2;
            return mn;
        }
        if(mouse_y>345 && mouse_y<425)
            {
            mn=3;
            return mn;
        }
        ///pour quitter le jeu
        if(mouse_y>480 && mouse_y<560)
            exit(0);
    }
}


void Menu::choixmenu1(int mn, Graph *g)
{

    switch(mn)
    {
    case 1:
        clear_bitmap(screen);


        g->make_example();

        break;

    case 2:
        clear_bitmap(screen);




        g->make_example();


        break;

    case 3:

        clear_bitmap(screen);


        g->make_example();

        break;
    }

}

Menu::Menu()
{
    ///boite du menu2
    m_menu2.set_frame(600, 420, 200, 180);
    m_menu2.set_bg_color(GRISCLAIR);
    m_menu2.set_moveable();

    ///boite titre
    m_menu2.add_child( m_titre );
    m_titre.set_dim(180, 20);
    m_titre.set_gravity_y( grman::GravityY::Up );


    ///message : sous-menu
    m_titre.add_child( m_ssmenu );
    m_ssmenu.set_message("SOUS-MENU");
    m_ssmenu.set_gravity_y(grman::GravityY::Up );


    ///bouton ajout
    m_menu2.add_child( m_bnouveau );
    m_bnouveau.set_frame(12,40,180,30);
    m_bnouveau.set_bg_color(BLEU);

    ///message ajout
    m_bnouveau.add_child(m_nouveau);
    m_nouveau.set_message("Nouvelle espèce");

    ///boite enlever
    m_menu2.add_child( m_benlever );
    m_benlever.set_frame(12,80,180,30);
    m_benlever.set_bg_color(BLEU);

    ///messge enlever
    m_benlever.add_child(m_enlever);
    m_enlever.set_message("Annuler espèce");

    ///boite retour
    m_menu2.add_child( m_bretour );
    m_bretour.set_frame(12,120,180,30);
    m_bretour.set_bg_color(BLEU);

    ///message retour
    m_bretour.add_child(m_retour);
    m_retour.set_message("Retour au menu");






}

/*void Menu::Menu2Update()
{
    m_menu2.update();

   if ( m_bnouveau.clicked() )
    {
        std::cout << "Nouvelle espèce" << std::endl;
    }

     if ( m_benlever.clicked() )
    {
        std::cout << "Annuler espèce" << std::endl;
    }

     if ( m_bretour.clicked() )
    {
        std::cout << "retour au menu" << std::endl;

    }
}
*/




