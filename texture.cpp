#include "texture.h"


Texture::Texture(void)
{
}


Texture::~Texture(void)
{
}

Texture:: Texture(string id, string file, float texlength_S, float texlength_T){
	this->id=id;
	this->file=file;
	this->texlength_S=texlength_S;
	this->texlength_T=texlength_T;

}

string Texture::getID(){
	return id;
}

string Texture::getFile(){
	return file;
}
float Texture::getTexLengthS(){
	return texlength_S;
}
float Texture::getTexLengthT(){
	return texlength_T;
}

void Texture::setID(string id){
	this->id=id;
}

void Texture::setFile(string file){
	this->file=file;
}

void Texture::setTexLengthS(float texlength_S) {
	this->texlength_S=texlength_S;
}
void Texture::setTexLengthT(float texlength_T){
	this->texlength_T=texlength_T;
}