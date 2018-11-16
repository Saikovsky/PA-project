#include "path_algorithm.h"


void randomize_vertices(unsigned int size, std::vector<float>&vertices)
{
    for (int i =0; i<size; i++)
    {
        float a = ((rand()%20)+(-10));
        a = a/10;
        if((i+1)%3==0)
        {
            vertices.push_back(0.0f);
        } else{
            vertices.push_back(a);
        }
    }
}

void generate_indices(std::vector<unsigned int>&indices,unsigned int ELEMENTS, unsigned int first)
{
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
}


int path_algorithm(unsigned int ELEMENTS, std::vector<float>&vertices, std::vector<unsigned int>&indices)
{
    unsigned int size = ELEMENTS*3;
    unsigned int first = 0;


    randomize_vertices(size, vertices);
    generate_indices(indices,ELEMENTS,first);

    std::vector<float> range_from_center;

    for (int i =0 ;i<size;i++)
    {
        if((i+1)%3==0)
        {
            range_from_center.push_back(sqrt(pow(vertices[i-2],2)+pow(vertices[i-1],2)));
        }
    }

    std::vector<float>::iterator max = std::max_element(range_from_center.begin(),range_from_center.end());
    int max_range_at = std::distance(range_from_center.begin(),max);

    int tab_break = max_range_at*3;
    std::vector<float> point;
    for(int i = tab_break;i<tab_break+3;i++)
    {
        point.push_back(vertices[i]);
    }
    //std::cout<<point[0]<<point[1]<<point[2]<<std::endl;
    std::vector<float> range_from_point;
    for (int i =0 ;i<vertices.size();i++)
    {
        if((i+1)%3==0)
        {
            range_from_point.push_back(sqrt(pow(vertices[i-2]-point[0],2)+pow(vertices[i-1]-point[1],2)));
        }

    }
    //std::vector<float>::iterator min_range_from_point = std::min_element(range_from_point.begin(),range_from_point.end());
    //int min_at = std::distance(range_from_point.begin(),min_range_from_point);
    //range_from_point.erase(range_from_point.begin()+min_at);
    //min_range_from_point = std::min_element(range_from_point.begin(),range_from_point.end());
    //min_at = std::distance(range_from_point.begin(),min_range_from_point);
    //std::cout<<*min_range_from_point;
    for(int i =0; i<ELEMENTS;i++)
    {
        std::cout<<range_from_point[i]<<std::endl;
    }
    return 0;

}