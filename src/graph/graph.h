/*
 * Ces classes sont une surcouche aux graphes boost
 * Les fonctionnalités attendues sont :
 *  - creation de graphe
 * 	- ajout de sommet
 * 	- coloration de sommet
 * (hésitez pas à en rajouter)
 */
 
 typedef int color;
 
 class Vertex {
	public:
		Vertex();
		color getColor();
		void setColor(color newColor);
	private:
		color vertexColor;
 };
 
class Graph {
	public:
		Graph();
		Vertex * addVertex();
};
