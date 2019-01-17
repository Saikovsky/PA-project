#include "path_algorithm.h"
#include <fstream>
#include <string>
#include <sstream>

void randomize_vertices(unsigned int size, std::vector<float>&vertices)
{
    for (int i =0; i<size; i++)
    {
        float a = ((rand()%2000)+(-1000));
        a = a/1000;
        if((i+1)%3==0)
        {
            vertices.push_back(0.0f);
        } else{
            vertices.push_back(a);
        }
    }
}

void generate_indices(std::vector<unsigned int>&indices,unsigned int ELEMENTS, unsigned int first, std::vector<int>&index)
{
    unsigned int triplet = ELEMENTS % 3;
    if(triplet!=0)
    {
     ELEMENTS = ELEMENTS - triplet;
    }
        for (unsigned int i =0; i<ELEMENTS; i++)
        {
            indices.push_back(i);
            if((i+1)%3==0)
            {
                indices.push_back(first);
                first+=3;
            }
            else {
                indices.push_back(i + 1);
            }
        }


    //for (float x:indices) std::cout<<x<<std::endl;
}

void index_of_furthest(std::vector<float>&vertices, std::vector<float>&temp_vertices);

void find_nearby(std::vector<float>&vertices, int index_of_first_child, std::vector<float>&temp_vertices);


int path_algorithm(unsigned int ELEMENTS, std::vector<float>&vertices, std::vector<unsigned int>&indices)
{

    std::vector<float> temp_vertices;
    unsigned int size = ELEMENTS*3;
    unsigned int first = 0;

    std::vector<int>index;
    randomize_vertices(size, vertices);
    generate_indices(indices,ELEMENTS,first,index);

    while(!vertices.empty())
    {
        index_of_furthest(vertices,temp_vertices);
    }

    vertices.clear();
    for(float x:temp_vertices) vertices.push_back(x);

    return 0;


}

void index_of_furthest(std::vector<float>&vertices, std::vector<float>&temp_vertices)
{
    int index_of_first_child;
    std::vector<float> range;
    for(int i = 0; i<vertices.size();i=i+3)
    {
        range.push_back(sqrt(pow(vertices[i],2)+pow(vertices[i+1],2)));
    }
    index_of_first_child=3*std::distance(range.begin(), std::max_element(range.begin(),range.end()));

    for (int i = 0; i < 3; i++) {
        temp_vertices.push_back(vertices[index_of_first_child + i]);
    }
    vertices.erase(vertices.begin() + index_of_first_child, vertices.begin() + (index_of_first_child + 3));
    if(vertices.size()>6)
    {
        find_nearby(vertices, index_of_first_child, temp_vertices);
        //find_nearby(vertices, index_of_first_child, temp_vertices);
    }
}

void find_nearby(std::vector<float>&vertices, int index_of_first_child, std::vector<float>&temp_vertices)
{
    int nearby_index;
    static int index = 0;
    std::vector<float> range;
    for(int i = 0; i<vertices.size();i=i+3)
    {
        range.push_back(sqrt(pow((temp_vertices[index]-vertices[i]),2)+pow((temp_vertices[index+1]-vertices[i+1]),2)));

    }
    //for(float x:range) std::cout<<"RANGE : "<<x<<std::endl;
    nearby_index=3*std::distance(range.begin(), std::min_element(range.begin(),range.end()));
    for(int i=0 ; i<3; i++)
    {
        temp_vertices.push_back(vertices[nearby_index+i]);
    }
    if(vertices.size()>=3)
    {
        vertices.erase(vertices.begin()+nearby_index,vertices.begin()+(nearby_index+3));
    }
    range.clear();
    for(int i = 0; i<vertices.size();i=i+3)
    {
        range.push_back(sqrt(pow((temp_vertices[index]-vertices[i]),2)+pow((temp_vertices[index+1]-vertices[i+1]),2)));

    }
    //for(float x:range) std::cout<<"RANGE : "<<x<<std::endl;
    nearby_index=3*std::distance(range.begin(), std::min_element(range.begin(),range.end()));
    for(int i=0 ; i<3; i++)
    {
        temp_vertices.push_back(vertices[nearby_index+i]);
    }
    if(vertices.size()>=3)
    {
        vertices.erase(vertices.begin()+nearby_index,vertices.begin()+(nearby_index+3));
    }
    //std::cout<<index<<std::endl;
    index+=9;
}