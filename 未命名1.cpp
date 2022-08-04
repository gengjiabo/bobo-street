#include<bits/stdc++.h>
using namespace std;
import numpy as np
import wxgl
import wxgl.glplot as glt

def red_heart(r, slices=100, thick=2.0, shift=(0,0,0)):
    """返回红心顶点数据"""
    
    a = np.linspace(0, 2*np.pi, slices)
    b = np.linspace(0.5*np.pi, -0.5*np.pi, slices)
    lons, lats = np.meshgrid(a, b)
    w = np.sqrt(np.abs(a - np.pi)) * thick
    x = r * np.cos(lats) * np.sin(lons) * w + shift[0]
    y = -r * np.cos(lats) * np.cos(lons) * w + shift[1]
    z = r * np.sin(lats) + shift[2]
    
    return x, y, z

def heart_beat(t):
    """心跳函数"""
    
    t %= 1000
    if t < 300:
        scale = 1 + t/3000
    elif t > 700:
        scale = 1 + (1000-t)/3000
    else:
        scale = 1.1
    
    return (scale,)

def arrow_fly(t):
    """丘比特之箭飞行函数"""
    
    t %= 4000
    if t > 2000:
       return ((0,-2,40-t/100),)
    else:
       return ((0,-2,0),)

def heart_fly(t):
    """丘比特之箭飞行函数"""
    
    t %= 4000
    if t > 2000:
       return ((0,0,1,90), (0,-2,40-t/100))
    else:
       return ((0,0,1,90), (0,-2,0))

glt.figure(azim=50, elev=16, style='gray') 
glt.mesh(*red_heart(2), color='crimson', transform=heart_beat) 

x, y, z = red_heart(0.2, thick=3.0, shift=(0,-8,0)) 
glt.mesh(x, -z, y, color='crimson', transform=heart_fly) 

light = wxgl.SunLight(roughness=0, metalness=0, shininess=0.5) 
glt.cylinder((0,0,-8), (0,0,9), 0.1, color='goldenrod', transform=arrow_fly, light=light) 

vs = [(-1,1,11), (1,-1,11), (1,-1,6), (-1,1,6),(-1,-1,11), (1,1,11), (1,1,6), (-1,-1,6)] 
texture = wxgl.Texture(r'res\feather.png') 
texcoord = [(0,1), (0,0), (1,0), (1,1),(0,1), (0,0), (1,0), (1,1)] 
light = wxgl.BaseLight() 
glt.quad(vs, texture=texture, texcoord=texcoord, transform=arrow_fly, light=light) 

glt.show()
int main()
{
	
	return 0;
}
