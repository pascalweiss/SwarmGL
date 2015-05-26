unit dan_geo_u;

interface

uses math;

const
  _rad2deg=180/pi;
  _deg2rad=pi/180;

type
  //vector
  Tv=record
    x,y,z:single;
  end;

  //triangle
  TTri=array[0..2] of TV;

  //matrice
  Tm=array[0..2,0..2]of single;

//------------------------------------------
function rad2deg(rad:single):single;
function deg2rad(deg:single):single;
function deg_norm(d:single):single;

//------------------------------------------
function v_fill(x,y,z:single):Tv;
function v_add(v1,v2:Tv):Tv;
function v_sub(v1,v2:tv):tv;
function v_norm(var v:tv):tv;
function v_len(v:Tv):Single;
function v_scale(v:Tv;sf:Single):tv;

function v_dot(v1,v2:tv):single;
function v_cross(v1,v2:tv):tv;
function v_angle(v1,v2:tv):single;
function v_angle_deg(v1,v2:tv):single;


function v_iszero(v:tv;tol:single):boolean;
function v_min_max(v:tv;min,max:single):tv;
function v_distance(v1,v2:tv):single;
function v_rot_x(v:tv;rad:extended):tv;
function v_rot_x_deg(v:tv;deg:extended):tv;
function v_rot_y(v:tv;rad:extended):tv;
function v_rot_y_deg(v:tv;deg:extended):tv;
function v_rot_z(v:tv;rad:extended):tv;
function v_rot_z_deg(v:tv;deg:extended):tv;

//------------------------------------------
function m_identity:tm;
function m_clr:tm;
function m_fill_rot_x(rad:single):tm;
function m_fill_rot_x_deg(deg:single):tm;
function m_fill_rot_y(rad:single):tm;
function m_fill_rot_y_deg(deg:single):tm;
function m_fill_rot_z(rad:single):tm;
function m_fill_rot_z_deg(deg:single):tm;
function m_mul(m1,m2:tm):tm;
function m_v_mul(m:tm;v:tv):tv;
function m_rot_xyz(rotx,roty,rotz:single):tm;
function m_rot_xyz_deg(deg_rotx,deg_roty,deg_rotz:single):tm;

//----------------------------------------------------
function tri_norm(tri:ttri):tv;

implementation

//------------------------------------------------------------------
// RADIAN AND DEGREE ANGLES
//------------------------------------------------------------------

//converts the radian number to the equivalent number in degrees
function rad2deg(rad:single):single;
begin
  result:=rad*_rad2deg;
end;

//converts the degree number to the equivalent number in radians
function deg2rad(deg:single):single;
begin
  result:=deg*_deg2rad;
end;

//konverts any degree number to a "normed" angle between 0-359
function deg_norm(d:single):single;
begin
  if d>360 then d:=d-360;
  if d<0 then d:=360+d;
  if d=360 then d:=0;
  result:=d;
end;


//------------------------------------------------------------------
// VECTOR
//------------------------------------------------------------------

//set vector position
function v_fill(x,y,z:single):Tv;
begin
  result.x:=x;
  result.y:=y;
  result.z:=z;
end;

{-------------------------------------------------
  *              *-----2*           *
  1              1                 /
  |              |               /
  |-----2*   ==> |         ==> /
}
function v_add(v1,v2:Tv):Tv;
begin
  Result:=v_fill(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
end;

{------------------------------------------------
        *       *------2*            *
        1       1                  /
        |       |                /
  *2-----   ==>            ==> /
}
function v_sub(v1,v2:tv):tv;
begin
  Result:=v_fill(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
end;


//length of vector
function v_len(v:Tv):Single;
begin
   result:=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
end;

//normalize vector to len=1
function v_norm(var v:tv):tv;
var
  len:single;
begin
  len:=v_len(v);if len=0 then len:=1;
  result.x:=v.x/len;
  result.y:=v.y/len;
  result.z:=v.z/len;
end;

//make vector longer/shorter
function v_scale(v:Tv;sf:Single):tv;
begin
  result.x:=v.x*sf;
  result.y:=v.y*sf;
  result.z:=v.z*sf;
end;

{
  vector-dot-product:
  need to calculate the angle between two vectors
}
function v_dot(v1,v2:tv):single;
begin
  result:=v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
end;

//calculate angle between two vectors
function v_angle(v1,v2:tv):single;
var
  vdot,vlen1,vlen2:single;
begin
  vdot:=v_dot(v1,v2);
  vlen1:=v_len(v1);
  vlen2:=v_len(v2);
  result:=arccos(vdot/(vlen1*vlen2));
end;

function v_angle_deg(v1,v2:tv):single;
begin
  result:=rad2deg(v_angle(v1,v2));
end;
        {
  if escape_v.x<>0 then rotation_v.x:=deg_norm(rad2deg(arctan(escape_v.y/escape_v.x)));
  if escape_v.y<>0 then rotation_v.z:=deg_norm(rad2deg(arctan(escape_v.x/escape_v.y)));
  if escape_v.z<>0 then rotation_v.y:=deg_norm(rad2deg(arctan(escape_v.x/escape_v.z)));
}

{
  //sinus kosinus für rotation
  //radius:=dan_geo_u.v_len(position_v);
  radius:=dan_geo_u.v_len(position_v);
  radius:=radius;
  escape_v.x:=radius*cos(main_f.periode);
  escape_v.y:=radius*sin(main_f.periode);
  escape_v.z:=0;
  escape_v:=v_norm(escape_v);
  escape_v:=v_scale(escape_v,1);
  position_v:=dan_geo_u.v_add(position_v,escape_v);
  exit;
}

{
  //sinus kosinus - funktioniert absolut
  position_v.x:=radius*cos(degtorad(main_f.periode));
  position_v.z:=radius*sin(degtorad(main_f.periode));
  //position_v.y:=radius*sin(degtorad(main_f.periode));
}


{
//punkte sttt fische
if distance=0 then exit;
if distance<10 then
begin
  distance:=sqr(10/(distance));
  glPointSize(2+distance);
  glBegin(GL_POINTS);
    glVertex3f(0,0,0);
  glEnd();
end;
}

{
    //implosion durch rictungsvektoren
    center_v:=position_v;
    center_v:=v_scale(center_v,-1);
    dir_v:=escape_v;
    v:=v_sub(center_v,dir_v);
    v:=v_norm(v);
    v:=v_scale(v,0.01);
    escape_v:=v;
    position_v:=dan_geo_u.v_add(position_v,escape_v);

}

  {
  //-----------------------------------------
  //punkte statt fische
  if distance<10 then
  begin
    gltranslatef(position_v.x,position_v.y,position_v.z);
    distance:=sqr(10/(distance));
    glPointSize(2+distance);
    glBegin(GL_POINTS);
      glVertex3f(0,0,0);
    glEnd();
  end;
  }

  {
  //escape-vectors
  if escape_c>0 then
  begin
    glPointSize(4);
    glColor3f(1,0.5,0.5);
    glBegin(GL_LINES);
    v:=dan_geo_u.v_norm(escape_v);
    v:=v_scale(v,0.1);
    glVertex3f(position_v.x,position_v.y,position_v.z);
    v:=dan_geo_u.v_add(position_v,v);
    glVertex3f(v.x,v.y,v.z);
    glEnd;
  end;
  }

{
  vector cross product:
  => normale of the plane given by v1 and v2

  change of v1 and v2 => negative vector

  right hand rule:
    v1=trigger finger
    v2=middle finger,
    => cross=thumb
}
function v_cross(v1,v2:tv):tv;
begin
  result.x:=v1.y*v2.z-v1.z*v2.y;
  result.y:=v1.z*v2.x-v1.x*v2.z;
  result.z:=v1.x*v2.y-v1.y*v2.x;
end;

//rotate vector about x-axis
function v_rot_x(v:tv;rad:extended):tv;
var
  asin,acos:extended;
begin
  math.SinCos(rad,asin,acos);
  result.x:=v.x;
  result.y:=v.y*acos-v.z*asin;
  result.z:=v.y*asin+v.z*acos;
end;

function v_rot_x_deg(v:tv;deg:extended):tv;
begin
  result:=v_rot_x(v,deg2rad(deg));
end;

//rotate vector about y-axis
function v_rot_y(v:tv;rad:extended):tv;
var
  asin,acos:extended;
begin
  math.SinCos(rad,asin,acos);
  result.x:=v.x*acos+v.z*asin;
  result.y:=v.y;
  result.z:=-v.x*asin+v.z*acos;
end;

function v_rot_y_deg(v:tv;deg:extended):tv;
begin
  result:=v_rot_y(v,deg2rad(deg));
end;

//rotate vector avout z-axis
function v_rot_z(v:tv;rad:extended):tv;
var
  asin,acos:extended;
begin
  math.SinCos(rad,asin,acos);
  result.x:=v.x*acos-v.y*asin;
  result.y:=v.x*asin+v.y*acos;
  result.z:=v.z;
end;

function v_rot_z_deg(v:tv;deg:extended):tv;
begin
  result:=v_rot_z(v,deg2rad(deg));
end;

//check if vector is nearly zero
function v_iszero(v:tv;tol:single):boolean;
begin
  result:=false;
  if abs(v.x)>tol then exit;
  if abs(v.y)>tol then exit;
  if abs(v.z)>tol then exit;
  result:=true;
end;

function v_min_max(v:tv;min,max:single):tv;
begin
  if abs(v.x)<min then v.x:=min;
  if abs(v.y)<min then v.y:=min;
  if abs(v.z)<min then v.z:=min;
  if abs(v.x)>max then v.x:=max;
  if abs(v.y)>max then v.y:=max;
  if abs(v.z)>max then v.z:=max;
  result:=v;
end;

//distance between two points
function v_distance(v1,v2:tv):single;
begin
  result:=sqrt(
    (v1.x-v2.x)*(v1.x-v2.x)+
    (v1.y-v2.y)*(v1.y-v2.y)+
    (v1.z-v2.z)*(v1.z-v2.z)
  );
end;

//------------------------------------------------------------------
// MATRICE
//------------------------------------------------------------------

{


Matrizen:

Identitätsmatrix lässt Vekor unverändert:

1 0 0 0     vx     vx
0 1 0 0  *  vy  =  vy
0 0 1 0     vz     vz
0 0 0 1     vw     vw

Translationsmatrix zum Verschieben:

1 0 0 x     vx     vx*1+w*x
0 1 0 y  *  vy  =  vy*1+w*y
0 0 1 z     vz     vz*1+w*z
0 0 0 1     vw     vw*1

Rotationsmatrix Z-Achse:

cos -sin 0 0
sin  cos 0 0
 0    0  1 0
 0    0  0 1

Rotationsmatrix X-Achse:

1   0    0  0
0  cos -sin 0
0  sin  cos 0
0   0    0  1

Rotationsmatrix Y-Achse:

 cos 0 sin 0
  0  0  0  0
-sin 0 cos 0
 0   0  0  1

}


{
    1 0 0         m[0,0]=1 m[1,0]=0 m[2,0]=0
  ( 0 1 0 )  <=>  m[0,1]=0 m[1,1]=1 m[2,1]=0
    0 0 1         m[0,2]=0 m[1,2]=0 m[2,2]=1
}
function m_identity:tm;
begin
  result[0,0]:=1;result[1,0]:=0;result[2,0]:=0;
  result[0,1]:=0;result[1,1]:=1;result[2,1]:=0;
  result[0,2]:=0;result[1,2]:=0;result[2,2]:=1;
end;

//clear matrix
function m_clr:tm;
var
  c,r:integer;
begin
  for r:=0 to 2 do
    for c:=0 to 2 do
      result[c,r]:=0;
end;

//create x-rotation-matrix
function m_fill_rot_x(rad:single):tm;
var
  acos,asin:single;
begin
  asin:=sin(rad);
  acos:=cos(rad);
  result[0,0]:=1;result[1,0]:=   0;result[2,0]:=    0;
  result[0,1]:=0;result[1,1]:=acos;result[2,1]:=-asin;
  result[0,2]:=0;result[1,2]:=asin;result[2,2]:= acos;
end;

function m_fill_rot_x_deg(deg:single):tm;
begin
  result:=m_fill_rot_x(deg2rad(deg));
end;

//create y-rotation-matrix
function m_fill_rot_y(rad:single):tm;
var
  acos,asin:single;
begin
  asin:=sin(rad);
  acos:=cos(rad);
  result[0,0]:= acos;result[1,0]:=0;result[2,0]:=asin;
  result[0,1]:=    0;result[1,1]:=1;result[2,1]:=   0;
  result[0,2]:=-asin;result[1,2]:=0;result[2,2]:=acos;
end;

function m_fill_rot_y_deg(deg:single):tm;
begin
  result:=m_fill_rot_y(deg2rad(deg));
end;

//create z-rotation-matrix
function m_fill_rot_z(rad:single):tm;
var
  acos,asin:single;
begin
  asin:=sin(rad);
  acos:=cos(rad);
  result[0,0]:=acos;result[1,0]:=-asin;result[2,0]:=0;
  result[0,1]:=asin;result[1,1]:= acos;result[2,1]:=0;
  result[0,2]:=   0;result[1,2]:=    0;result[2,2]:=1;
end;

function m_fill_rot_z_deg(deg:single):tm;
begin
  result:=m_fill_rot_z(deg2rad(deg));
end;

//multiplikation of two matrices
function m_mul(m1,m2:tm):tm;
begin
  result[0,0]:=m1[0,0]*m2[0,0]+m1[1,0]*m2[0,1]+m1[2,0]*m2[0,2];
  result[1,0]:=m1[0,0]*m2[1,0]+m1[1,0]*m2[1,1]+m1[2,0]*m2[1,2];
  result[2,0]:=m1[0,0]*m2[2,0]+m1[1,0]*m2[2,1]+m1[2,0]*m2[2,2];

  result[0,1]:=m1[0,1]*m2[0,0]+m1[1,1]*m2[0,1]+m1[2,1]*m2[0,2];
  result[1,1]:=m1[0,1]*m2[1,0]+m1[1,1]*m2[1,1]+m1[2,1]*m2[1,2];
  result[2,1]:=m1[0,1]*m2[2,0]+m1[1,1]*m2[2,1]+m1[2,1]*m2[2,2];

  result[0,2]:=m1[0,2]*m2[0,0]+m1[1,2]*m2[0,1]+m1[2,2]*m2[0,2];
  result[1,2]:=m1[0,2]*m2[1,0]+m1[1,2]*m2[1,1]+m1[2,2]*m2[1,2];
  result[2,2]:=m1[0,2]*m2[2,0]+m1[1,2]*m2[2,1]+m1[2,2]*m2[2,2];
end;

//multiplication of a matrix with a vector
function m_v_mul(m:tm;v:tv):tv;
begin
  result.x:=m[0,0]*v.x+m[1,0]*v.y+m[2,0]*v.z;
  result.y:=m[0,1]*v.x+m[1,1]*v.y+m[2,1]*v.z;
  result.z:=m[0,2]*v.x+m[1,2]*v.y+m[2,2]*v.z;
end;


{
         |  CE      -CF       D   |
    M  = |  BDE+AF  -BDF+AE  -BC  |
         | -ADE+BF   ADF+BE   AC  |
}
function m_rot_xyz(rotx,roty,rotz:single):tm;
var
  a,b,c,d,e,f,ad,bd:extended;
begin
  math.SinCos(rotx,b,a);
  math.SinCos(roty,d,c);
  math.SinCos(rotz,f,e);

  ad:=a*d;
  bd:=b*d;

  result[0,0]:=      c*e;result[1,0]:=     -c*f;result[2,0]:=   d;
  result[0,1]:= bd*e+a*f;result[1,1]:=-bd*f+a*e;result[2,1]:=-b*c;
  result[0,2]:=-ad*e+b*f;result[1,2]:= ad*f+b*e;result[2,2]:= a*c;


  {
   A       := cos(rotx);
   B       := sin(rotx);
   C       := cos(roty);
   D       := sin(roty);
   E       := cos(rotz);
   F       := sin(rotz);
  }
end;

function m_rot_xyz_deg(deg_rotx,deg_roty,deg_rotz:single):tm;
begin
  result:=m_rot_xyz(deg2rad(deg_rotx),deg2rad(deg_roty),deg2rad(deg_rotz));
end;


//------------------------------------------------------------------
// TRIANGLE
//------------------------------------------------------------------

//senkrechte zu dreieck?
function tri_norm(tri:ttri):tv;
var
  v1,v2:Tv;
begin
  v1:=v_sub(Tri[0],Tri[1]);
  v2:=v_sub(Tri[1],Tri[2]);
  result:=v_cross(v1,v2);
  result:=v_norm(result);
end;


end.

