/*
 * Cette classe est une surcouche aux graphes boost
 * Les fonctionnalités attendues sont :
 *  - creation de graphe
 * 	- ajout de sommet
 * 	- coloration de sommet
 * (hésitez pas à en rajouter)
 */
 
 typedef color int;
 
 class Vertex {
	public:
		Vertex();
		color getColor();
		void setColor(color newColor);
 }
 
class Graph {
	public:
		Graph();
		Vertex * addVertex();
}
