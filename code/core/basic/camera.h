
//三维世界的摄像机

#include "../../includes.h"

class camera
{
public:
protected:
private:
    Vector3 m_pos;
    Vector3 m_up;
    Vector3 m_view;

    //可视距离
    float m_far;
    float m_near;

    //水平视野
    float m_fov;

    //宽高比
    float m_ratio;
}