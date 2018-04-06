#include "graph.h"
#include <fstream>
/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx,float crs, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_top_box.add_child( m_box_label_crs );
    m_box_label_crs.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_box_label_crs.set_dim(10,10);
    m_box_label_crs.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_box_label_crs.add_child( m_label_crs );
    m_label_crs.set_message( std::to_string(crs) );
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
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
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
    m_retour.set_message("Sauvegarder");
}

void Graph::lectureFichier(std::string fichS,std::string fichA)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    std::ifstream fichier(fichS, std::ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        int nb_sommet;

        fichier >> nb_sommet;

        for (int i=0; i<nb_sommet; i++)
        {
            int ind,x,y;
            double N,R;
            std::string img;
            fichier >> ind >> N >> R >> x >> y >> img;
            add_interfaced_vertex(ind,N,R,x,y,img);
        }


        fichier.close();  // on ferme le fichier
    }

    std::ifstream fich(fichA, std::ios::in);  // on ouvre le fichier en lecture
    if(fich)  // si l'ouverture a réussi
    {
        int nb_arete;
        fich >> nb_arete;

        for (int i=0; i<nb_arete; i++)
        {
            int ind,S1,S2;
            double Weight;
            fich >> ind >> S1 >> S2 >> Weight;
            add_interfaced_edge(ind, S1, S2, Weight);

        }


        fich.close();  // on ferme le fichier
    }

    else  // sinon
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}

void Graph::sauvegarde(std::string SfichS,std::string SfichA)
{
    int idx,x, y, pic_idx=0, vert1, vert2;
    double value, weight=0;


    std::string pic_name="";

    std::ofstream fichier(SfichS, std::ios::out | std::ios::trunc);
   // update(u);
   // grman::mettre_a_jour();

    fichier<<m_vertices.size()<<"\n";


    for(int i=0; i<m_vertices.size(); i++)
    {
        fichier<<m_vertices[i].m_interface->m_label_idx.get_message();
        fichier<<" "<<m_vertices[i].m_interface->m_label_value.get_message();
        fichier<<" "<<m_vertices[i].m_interface->m_label_crs.get_message();
        fichier<<" "<<m_vertices[i].m_interface->m_top_box.get_posx();
        fichier<<" "<<m_vertices[i].m_interface->m_top_box.get_posy();
        fichier<<" "<<m_vertices[i].m_interface->m_img.get_pic_name()<<"\n";
    }

    fichier.close();

    std::ofstream fich(SfichA, std::ios::out | std::ios::trunc);

    fich<<m_vertices.size()<<"\n";


    for(int i=0; i<m_edges.size(); i++)
    {
        fich<<i; //id
        fich<<" "<<m_edges[i].m_from; //S1
        fich<<" "<<m_edges[i].m_to; //S2
        fich<<" "<<m_edges[i].m_interface->m_slider_weight.get_value()<<"\n"; //poid
    }

}
void Graph::update(int &u)
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

        if ( m_interface->m_bnouveau.clicked() )
    {
        std::cout << "Nouvelle espèce" << std::endl;

       //Ajoutespece(m_vertices,m_edges);

    }

     if ( m_interface->m_benlever.clicked() )
    {
        std::cout << "Annuler espèce" << std::endl;
    }

     if ( m_interface->m_bretour.clicked() )
    {
        std::string SfichierS,SfichierA;
        std::cout << "Sauvegarde effectuee" << std::endl;
        if (u==1)
        {
            SfichierS="sforet.txt";
            SfichierA="aforet.txt";
            sauvegarde(SfichierS,SfichierA);
        }

        else if (u==2)
        {
            SfichierS="sjungle.txt";
            SfichierA="ajungle.txt";
            sauvegarde(SfichierS,SfichierA);
        }

        if (u==3)
        {
            SfichierS="smers.txt";
            SfichierA="amers.txt";
            sauvegarde(SfichierS,SfichierA);
        }
    }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value,float crs, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx,crs, x, y, pic_name, pic_idx);
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

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
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


void Menu::choixmenu1(int mn, Graph *g,int &u)
{
    std::string fichS;
    std::string fichA;
    switch(mn)
    {
    case 1:
        clear_bitmap(screen);


        //g->make_example();
        fichS="sforet.txt";
        fichA="aforet.txt";
        g->lectureFichier(fichS, fichA);
        u=1;
        break;

    case 2:
        clear_bitmap(screen);

        fichS="sjungle.txt";
        fichA="ajungle.txt";
        //g->make_example();
        g->lectureFichier(fichS, fichA);
        u=2;

        break;

    case 3:

        clear_bitmap(screen);

        fichS="smers.txt";
        fichA="amers.txt";
        //g->make_example();
        g->lectureFichier(fichS, fichA);
        u=3;
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
    m_retour.set_message("Sauvegarder");

}


/*/// eidx index of edge to remove
/*void Graph::test_remove_edge(int eidx)
{
/// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
        {
    /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
    /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
/* m_interface->m_main_box.add_child(ei->m_top_edge); */
/* m_edges[idx] = Edge(weight, ei);
/// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
}

/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
std::vector<int> &veto = m_vertices[remed.m_to].m_in;
vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
m_edges.erase( eidx );

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;

}*/

