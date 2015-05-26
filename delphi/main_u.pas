unit main_u;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,ExtCtrls, StdCtrls, ComCtrls,jpeg,inifiles,spin,
  //opengl unit
  DGLOpenGL,
  //own
  dan_geo_u;

const
  _cap='OpenGL Swarm Intelligence V1.0 2012 by Daniel Schwamm';
  _ini_fn='ogl_swarm.ini';

  //space dimension--------------
  _model_background_radius=50;

  //speed factors-------------------
  _my_rot_delta=1; //rotation speed adder

  //depth buffer
  _NearClipping=0.01;
  _FarClipping=2*_model_background_radius;

  _particle_max=100000;
  _particle_pos_start_radius=2;
  _particle_width=0.03;
  _particle_length=0.2;

  _raster_cell_dim=0.5;//0.5;
  _raster_radius=15;     //0.5 m * 4 = 2  meter  Radius, also 4 m Würfel

  _bullet_max=10;

type
  //-------------------------------------------
  tparticle = class(TObject)
  public
    pos_v:tv;
    //rotation_v:tv;
    dir_v:tv;
    density_escape_steps:integer;
    inertia_steps:integer;
    angle:single;
    //escape_len:single;
    r_col,g_col,b_col:single;

    enemy_escape_v:tv;
    enemy_escape_steps:integer;
    enemy_escape_steps_max:integer;
    enemy_escape_speed:single;
    enemy_escape_speed_delta:single;


    constructor create;
    procedure draw;
    procedure calc_pos;
  end;

  //-------------------------------------------
  tdensity = record
    count:integer;
    dir_v:tv;
  end;

  //-------------------------------------------
  tbullet = record
    quad:PGLUquadric;
    count:integer;
    pos_v:tv;
    dir_v:tv;
  end;

  //-------------------------------------------
  Tmain_f = class(TForm)
    model_frequency_t: TTimer;
    model_background_img: TImage;
    pctrl: TPageControl;
    navigation_ts: TTabSheet;
    density_escape_ts: TTabSheet;
    Label1: TLabel;
    navigation_pos_x_e: TEdit;
    Label2: TLabel;
    navigation_pos_y_e: TEdit;
    Label3: TLabel;
    navigation_pos_z_e: TEdit;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    navigation_rot_x_e: TEdit;
    Label7: TLabel;
    navigation_rot_y_e: TEdit;
    Label8: TLabel;
    navigation_rot_z_e: TEdit;
    Label9: TLabel;
    navigation_speed_sb: TScrollBar;
    view_border_p: TPanel;
    view_p: TPanel;
    model_ts: TTabSheet;
    Label10: TLabel;
    model_frequency_sb: TScrollBar;
    model_background_chb: TCheckBox;
    Label12: TLabel;
    density_max_e: TEdit;
    Label13: TLabel;
    density_allowed_se: TSpinEdit;
    Label14: TLabel;
    density_escape_e: TEdit;
    density_raster_chb: TCheckBox;
    enemy_escape_ts: TTabSheet;
    enemy_escape_viewer_chb: TCheckBox;
    Label16: TLabel;
    Label17: TLabel;
    enemy_escape_e: TEdit;
    Label18: TLabel;
    swarm_ts: TTabSheet;
    Label19: TLabel;
    swarm_radius_e: TEdit;
    TabSheet1: TTabSheet;
    Label21: TLabel;
    particle_center_speed_sb: TScrollBar;
    particle_rotation_speed_sb: TScrollBar;
    Label22: TLabel;
    Label11: TLabel;
    swarm_colored_chb: TCheckBox;
    swarm_particles_sb: TScrollBar;
    enemy_escape_distance_sb: TScrollBar;
    swarm_density_escape_color_chb: TCheckBox;
    swarm_enemy_escape_color_chb: TCheckBox;
    enemy_escape_steps_sb: TScrollBar;
    Label23: TLabel;
    enemy_escape_speed_sb: TScrollBar;
    Label15: TLabel;
    density_escape_steps_sb: TScrollBar;
    Label24: TLabel;
    density_escape_speed_sb: TScrollBar;
    particle_random_sb: TScrollBar;
    Label25: TLabel;
    bullet_img: TImage;
    swarm_filled_chb: TCheckBox;
    particle_inertia_l: TLabel;
    particle_inertia_sb: TScrollBar;
    swarm_inertia_color_chb: TCheckBox;
    Shape1: TShape;
    Shape2: TShape;
    Shape3: TShape;
    Shape4: TShape;
    Label20: TLabel;
    particle_synch_sb: TScrollBar;
    status_p: TPanel;
    density_raster_radius_sb: TScrollBar;
    Label26: TLabel;
    Label27: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormDestroy(Sender: TObject);
    procedure model_frequency_tTimer(Sender: TObject);
    procedure FormKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormResize(Sender: TObject);
    procedure model_frequency_sbChange(Sender: TObject);
    procedure view_pClick(Sender: TObject);
    procedure navigation_speed_sbChange(Sender: TObject);
    procedure density_allowed_seChange(Sender: TObject);
    procedure enemy_escape_viewer_chbClick(Sender: TObject);
    procedure swarm_density_escape_color_chbClick(Sender: TObject);
    procedure swarm_enemy_escape_color_chbClick(Sender: TObject);
    procedure particle_rotation_speed_sbChange(Sender: TObject);
    procedure particle_center_speed_sbChange(Sender: TObject);
    procedure swarm_particles_sbChange(Sender: TObject);
    procedure enemy_escape_distance_sbChange(Sender: TObject);
    procedure enemy_escape_steps_sbChange(Sender: TObject);
    procedure enemy_escape_speed_sbChange(Sender: TObject);
    procedure density_escape_steps_sbChange(Sender: TObject);
    procedure density_escape_speed_sbChange(Sender: TObject);
    procedure particle_random_sbChange(Sender: TObject);
    procedure model_background_chbClick(Sender: TObject);
    procedure swarm_colored_chbClick(Sender: TObject);
    procedure swarm_filled_chbClick(Sender: TObject);
    procedure particle_inertia_sbChange(Sender: TObject);
    procedure swarm_inertia_color_chbClick(Sender: TObject);
    procedure particle_synch_sbChange(Sender: TObject);
    procedure sbScroll(Sender: TObject;
      ScrollCode: TScrollCode; var ScrollPos: Integer);
    procedure density_raster_radius_sbChange(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
    home_dir:string;

    //opengl environment
    handle_dc:HDC;
    handle_rc:HGLRC;

    //my position and axis-angeles
    my_pos_v:tv;
    my_rot_v:tv;
    my_look_v:tv;
    my_pos_speed_delta:single;

    //key holder----------------
    active_key:word;
    active_ctrl:bool;

    //background----------------
    model_rotation_v:tv;
    model_background_ok:bool;
    model_background_quad:PGLUquadric;
    model_background_tx:gluint;

    //--------------------------------
    swarm_particles:integer;
    swarm_colored_ok:bool;
    swarm_filled_ok:bool;
    swarm_enemy_escape_color_ok:bool;
    swarm_inertia_color_ok:bool;
    swarm_density_escape_color_ok:bool;
    swarm_radius_max:single;

    //--------------------------------
    particle_rotation_speed:single;
    particle_center_speed:single;
    particle_inertia:byte;
    particle_random:byte;
    particle_random_max:byte;
    particle_synch:byte;
    particle_a:array[0.._particle_max] of TParticle;


    //--------------------------------

    //particle_escape_speed:single;

    raster_a:array[
      -_raster_radius.._raster_radius,
      -_raster_radius.._raster_radius,
      -_raster_radius.._raster_radius
    ]of tdensity;

    density_max:integer;
    density_raster_radius:integer;
    density_allowed_max:integer;
    density_escape_steps:integer;
    density_escape_speed:single;
    density_escape_count:integer;

    enemy_escape_viewer_ok:bool;
    enemy_escape_distance:single;
    enemy_escape_steps:integer;
    enemy_escape_speed:single;
    enemy_escape_count:integer;


    particle_density:integer;

    //-------------------------------------------
    bullet_tx:gluint;
    bullet_a:array[0.._bullet_max]of TBullet;

    //test
    test_d:single;

    //----------------------------------------
    procedure draw_scene;

    //---------------------------------------------------------------
    function CreateTexture(Width,Height:Word;pData:Pointer):Integer;
    function img2tx(img:timage):TGLuint;

    function intto1000er(l:extended):string;
    function float_to_string(d:single):string;overload;
    function float_to_string(d:single;dec:byte):string;overload;

  end;

var
  main_f: Tmain_f;

implementation

{$R *.dfm}

//------------------------------------------------------------
constructor tparticle.create;
begin
  pos_v:=v_fill(
    (random(1000*2*_particle_pos_start_radius)-1000*_particle_pos_start_radius)/500,
    (random(1000*2*_particle_pos_start_radius)-1000*_particle_pos_start_radius)/500,
    (random(1000*2*_particle_pos_start_radius)-1000*_particle_pos_start_radius)/500
  );
  dir_v:=v_fill(random(2)-1,random(2)-1,random(2)-1);
  dir_v:=v_norm(dir_v);
  dir_v:=v_scale(dir_v,(random(10)-5)/100);
  //dir_v:=v_fill(0,0,0);

  enemy_escape_steps:=0;
  density_escape_steps:=0;
  inertia_steps:=0;

  //set color with domination of blue
  r_col:=(random(100)+100)/255;
  g_col:=(random(100)+120)/255;
  b_col:=(random(100)+155)/255;
end;

//------------------------------------------------------------
procedure TParticle.calc_pos;

   //------------------------------------------------
  function get_particle_random(v:single):single;
  begin
    result:=v-(random(main_f.particle_random)/100)*v;
  end;

   //------------------------------------------------
  function get_particle_invers_random(v:single):single;
  begin
    result:=(random(100-main_f.particle_random)/100)*v;
  end;

   //------------------------------------------------
  function get_rotation_v:tv;
  var
    speed:single;
  begin
    //set rotation speed
    speed:=get_particle_random(main_f.particle_rotation_speed);
    //speed:=0.011;
    //orthogonaler vector 1
    result:=v_cross(pos_v,dir_v);
    //orthogonaler vector 2 to orthogonaler vector 1
    result:=v_cross(pos_v,result);
    //norm vector for scaling
    result:=v_norm(result);
    //scale direction vector with speed
    result:=v_scale(result,-speed);
  end;

  //------------------------------------------------
  function get_center_v:tv;
  var
    distance,speed:single;
  begin
    //get distance to middle point
    distance:=v_len(pos_v);
    //set speed to the middle
    speed:=get_particle_invers_random(main_f.particle_center_speed);
    //outer particles are faster as inner particles
    speed:=distance*distance*speed;
    //direction to middle point
    result:=v_scale(pos_v,-1);
    //norm vector for scaling
    result:=v_norm(result);
    //scale direction vector with speed
    result:=v_scale(result,speed);
  end;

  //------------------------------------------------
  function get_density_escape_v(var x,y,z:integer):tv;
  var
    speed,radius:single;
  begin
    //not in density raster
    x:=-1;

    //no density escape as standard
    result:=v_fill(0,0,0);

    //calculate distance to middle point
    radius:=v_len(pos_v);

    //save biggest radius
    if radius>main_f.swarm_radius_max then main_f.swarm_radius_max:=radius;

    //particle in density raster? if not get out!
    if radius>main_f.density_raster_radius*_raster_cell_dim then exit;

    //yes: calculate position to index of raster array
    x:=trunc(pos_v.x/_raster_cell_dim);
    y:=trunc(pos_v.y/_raster_cell_dim);
    z:=trunc(pos_v.z/_raster_cell_dim);

    //increment particle counter of the raster box
    main_f.raster_a[x,y,z].count:=main_f.raster_a[x,y,z].count+1;

    //add particle direction to raster box
    main_f.raster_a[x,y,z].dir_v:=v_add(main_f.raster_a[x,y,z].dir_v,dir_v);

    //save highest density
    if main_f.raster_a[x,y,z].count>main_f.density_max then main_f.density_max:=main_f.raster_a[x,y,z].count;

    //density escape acctive?
    if density_escape_steps=0 then
    begin
      //no: check if density in actual raster box is not to much!
      if main_f.raster_a[x,y,z].count<main_f.density_allowed_max then exit;

      //density alarm: set steps of density escape
      density_escape_steps:=trunc(get_particle_random(main_f.density_escape_steps));
    end;

    //density escape: to much particles, move away from middle point
    if density_escape_steps>main_f.density_escape_steps/2 then
    begin
      //first half of escape: speed goes slow to fast
      speed:=main_f.density_escape_steps-density_escape_steps;
      speed:=speed*speed;
    end
    else
    begin
      //last half of escape: speed goes fast to slow
      speed:=density_escape_steps*density_escape_steps;
    end;
    speed:=speed*main_f.density_escape_speed;
    speed:=get_particle_random(speed)/10000;
    result:=v_norm(pos_v);
    result:=v_scale(result,speed);

    //give escape stream some volume
    if abs(result.x)<abs(result.y) then result.x:=get_particle_random(density_escape_steps)*result.x;
    if abs(result.y)<abs(result.z) then result.y:=get_particle_random(density_escape_steps)*result.y;
    if abs(result.z)<abs(result.x) then result.z:=get_particle_random(density_escape_steps)*result.z;
  end;

  //------------------------------------------------
  function get_enemy_escape_v(distance:single;enemy_pos_v,rotation_v:tv;enemy_ok:bool):tv;
  var
    speed,len,d:single;
  begin
    result:=v_fill(0,0,0);

    //flucht-geschwindigkeit
    speed:=main_f.enemy_escape_distance-distance;

    //enemy active and in danger radius?
    if enemy_ok and(speed>0) then
    begin
      //yes: get in escape-mode
      inc(main_f.enemy_escape_count);

      //calculate escape direction
      enemy_escape_v:=dan_geo_u.v_sub(pos_v,enemy_pos_v);

      //allow some variations
      d:=1-get_particle_random(100)/100;if random(2)=1 then d:=-d;
      d:=d/10;
      enemy_escape_v.x:=enemy_escape_v.x+d;
      enemy_escape_v.y:=enemy_escape_v.y+d;
      enemy_escape_v.z:=enemy_escape_v.z+d;

      //normierung
      enemy_escape_v:=v_norm(enemy_escape_v);

      //je näher feind, desto gröser der impuls
      //speed:=speed/main_f.enemy_escape_distance;
      enemy_escape_v:=v_scale(enemy_escape_v,speed);

      //bestimme fluchtlänge
      len:=0.1+get_particle_random(main_f.enemy_escape_steps)/100;
      enemy_escape_steps_max:=trunc(len*get_particle_random(main_f.enemy_escape_steps));
      enemy_escape_steps:=enemy_escape_steps_max;

      //max 1 m/step
      enemy_escape_speed:=get_particle_random(main_f.enemy_escape_speed)/100;

      enemy_escape_speed_delta:=get_particle_random(enemy_escape_speed/(enemy_escape_steps_max/4));

      //deaktiviere dichteflucht
      density_escape_steps:=0;
    end;

    //im fluchtmodus? wenn nicht, dann raus
    if enemy_escape_steps<=0 then exit;

    //hälfte der fluchtstrecke geschafft?
    if enemy_escape_steps<enemy_escape_steps_max/3 then
    begin
      //bewege particle wieder zum zentrum hin
      inertia_steps:=0;

      //näher als ein meter vom zentrum entfernt? dann raus
      len:=v_len(pos_v)-random(2)+0.2;
      if len<0 then
      begin
        enemy_escape_steps:=0;
        exit;
      end;

      speed:=get_particle_random(len/50);
      if random(5)=0 then result:=rotation_v
                     else result:=v_scale(v_norm(pos_v),-speed);
      exit;
    end;

    //calculate escape speed: get lower with steps
    enemy_escape_speed:=enemy_escape_speed-enemy_escape_speed_delta;
    if enemy_escape_speed<0 then enemy_escape_speed:=0;
    if enemy_escape_speed<0.1 then enemy_escape_speed:=0.1;

    if random(5)=0 then result:=rotation_v
                   else result:=v_scale(enemy_escape_v,enemy_escape_speed);
  end;

var
  d,distance:single;
  r,x,y,z:integer;
  old_dir_v,rotation_v,v:tv;
begin
  x:=-1;y:=-1;z:=-1;

  //save old direction
  old_dir_v:=dir_v;

  //inertia-movement?
  if inertia_steps=0 then
  begin
    //no: calculate new rotation
    rotation_v:=get_rotation_v;

    //set new direction
    dir_v:=rotation_v;

    //calculate centering
    //if random(100)>=main_f.particle_random then
    begin
      v:=get_center_v;
      dir_v:=v_add(dir_v,v);
    end;

    if random(100)<=main_f.particle_random then
    begin
      d:=random(100)/100;//if(random(2)=1)then d:=-d;
      dir_v.x:=dir_v.x*d;
      d:=random(100)/100;//if(random(2)=1)then d:=-d;
      dir_v.y:=dir_v.y*d;
      d:=random(100)/100;//if(random(2)=1)then d:=-d;
      dir_v.z:=dir_v.z*d;
    end

  end
  else
  begin
    //yes: no rotation or centering
    rotation_v:=v_fill(0,0,0);
  end;

  //density escape
  v:=get_density_escape_v(x,y,z);
  dir_v:=v_add(dir_v,v);

  //particle in a raster box?
  if x<>-1 then
  begin
    //yes: set direction to middle direction of in the raster box
    if(random(100)>=main_f.particle_random)and(random(100)<=main_f.particle_synch) then
    begin
      dir_v:=v_add(dir_v,v_scale(main_f.raster_a[x,y,z].dir_v,random(main_f.particle_synch)/500));
    end;
  end;

  //viewer escape
  if main_f.enemy_escape_viewer_ok then
  begin
    //calculate distance to user
    distance:=dan_geo_u.v_distance(pos_v,main_f.my_pos_v);
    v:=get_enemy_escape_v(distance,main_f.my_pos_v,rotation_v,main_f.enemy_escape_viewer_ok);
    dir_v:=v_add(dir_v,v);
  end;

  //escape from bullets
  for r:=0 to _bullet_max-1 do
  begin
    //bullet active? if not then out
    if main_f.bullet_a[r].count<=0 then continue;
    //calculate distance between particle and bullet
    distance:=dan_geo_u.v_distance(pos_v,main_f.bullet_a[r].pos_v);
    //calculate diretion of escape from enemy
    v:=get_enemy_escape_v(distance,main_f.bullet_a[r].pos_v,rotation_v,true);
    //adapt actual direction
    dir_v:=v_add(dir_v,v);
  end;

  //inertia active or enemy_escape?
  if(density_escape_steps=0)and(enemy_escape_steps=0)and(inertia_steps=0) then
  begin
    //no: activising inertia?
    if(random(10)=1) and (random(100)>main_f.particle_random) then
    begin
      //yep: calculate steps
      inertia_steps:=trunc(get_particle_random(main_f.particle_inertia));
    end;
  end;

  //calculate new direction: mixture between old and new direction
  d:=random(100)/100;
  old_dir_v:=v_scale(old_dir_v,d);
  dir_v:=v_scale(dir_v,1-d);
  dir_v:=v_add(dir_v,old_dir_v);

  //set new position
  pos_v:=v_add(pos_v,dir_v);
end;

//------------------------------------------------------------
procedure tparticle.draw;
var
  //distance:single;
  color:single;
  v:tv;
begin
  //fluchtdauer rnterzählen
  dec(enemy_escape_steps);if enemy_escape_steps<0 then enemy_escape_steps:=0;
  if enemy_escape_steps>0 then inc(main_f.enemy_escape_count);
  dec(density_escape_steps);if density_escape_steps<0 then density_escape_steps:=0;
  if density_escape_steps>0 then inc(main_f.density_escape_count);
  dec(inertia_steps);if inertia_steps<0 then inertia_steps:=0;

  //neue position bestimmen
  //distance:=calc_position;
  pos_v:=v_min_max(pos_v,0.0001,_model_background_radius);

  calc_pos;

  //colorization of particles
  if main_f.swarm_colored_ok then
  begin
    color:=1;
    if main_f.swarm_inertia_color_ok and(inertia_steps>0) then
    begin
      //denisty-escape color red
      glColor3f(color,color,color);
    end
    else
    if main_f.swarm_density_escape_color_ok and(density_escape_steps>0) then
    begin
      //denisty-escape color red
      glColor3f(color,g_col,b_col);
    end
    else
    if main_f.swarm_enemy_escape_color_ok  and(enemy_escape_steps>0) then
    begin
      //enemy-escape color yellow (out) or green (in)
      if enemy_escape_steps<enemy_escape_steps_max/2 then glColor3f(color/2,color,b_col)
                                                     else glColor3f(color,color,b_col)
    end
    else
    begin
      //normal color: blue
      glColor3f(r_col,g_col,b_col);
    end;
  end;

  //spitze in bewegungsrichtung bestimen
  v:=dir_v;
  v:=dan_geo_u.v_norm(v);
  v:=dan_geo_u.v_scale(v,_particle_length);
  v:=dan_geo_u.v_add(pos_v,v);

  //partikel malen
  glBegin(GL_TRIANGLES);
  glVertex3f(pos_v.x,pos_v.y-_particle_width,pos_v.z);
  glVertex3f(pos_v.x,pos_v.y+_particle_width,pos_v.z);
  glVertex3f(v.x,v.y,v.z);
  glEnd();
end;

//------------------------------------------------------------
//PROCEDURES
//------------------------------------------------------------

//------------------------------------------------------------
procedure Tmain_f.FormCreate(Sender: TObject);

  procedure particles_create;
  var
    r:integer;
    particle:tparticle;
  begin
    for r:=0 to _particle_max-1 do
    begin
      particle:=tparticle.create;
      particle_a[r]:=particle;
    end;
  end;

var
  r:integer;
begin
  home_dir:=extractfilepath(application.exename);
  caption:=_cap;
  randomize;
  view_border_p.align:=alclient;
  view_p.align:=alclient;

  swarm_particles_sb.Max:=_particle_max;

  //intialize opengl
  handle_DC:=GetDC(view_p.Handle);
  if not InitOpenGL then Application.Terminate;
  handle_RC:=CreateRenderingContext(handle_DC,[opDoubleBuffered],24,32,0,0,0,0);
  ActivateRenderingContext(handle_DC,handle_RC);
  //glenable(GL_DEPTH_TEST);

  //create objects
  //model-background-----------------------------------------------
  model_background_quad:=gluNewQuadric;
  gluQuadricTexture(model_background_quad,TGLboolean(true));
  model_background_tx:=img2tx(model_background_img);

  bullet_tx:=img2tx(bullet_img);
  for r:=0 to _bullet_max-1 do
  begin
    bullet_a[r].quad:=gluNewQuadric;
    gluQuadricTexture(bullet_a[r].quad,TGLboolean(true));
    bullet_a[r].count:=0;
  end;

  particles_create;

  //start action
  //my_rotation_v:=v_fill(345,90,0);
  my_pos_v:=v_fill(0,0,10);
  my_rot_v:=v_fill(0,0,0);


  //deletefile(home_dir+_ini_fn);
  with tinifile.create(home_dir+_ini_fn) do
  begin
    pctrl.ActivePageIndex:=readinteger('param','activepageindex',0);

    model_frequency_sb.Position:=readinteger('model','freqency',model_frequency_sb.max);
    model_frequency_sbChange(nil);
    model_background_chb.checked:=readbool('model','background_ok',model_background_chb.checked);
    model_background_chbClick(nil);

    navigation_speed_sb.Position:=readinteger('navigation','speed',navigation_speed_sb.Position);
    navigation_speed_sbchange(nil);

    swarm_particles_sb.position:=readinteger('swarm','particles',swarm_particles_sb.position);
    swarm_particles_sbChange(nil);
    swarm_filled_chb.checked:=readbool('swarm','filled_ok',swarm_filled_chb.checked);
    swarm_filled_chbClick(nil);
    swarm_colored_chb.checked:=readbool('swarm','colored_ok',swarm_colored_chb.checked);
    swarm_colored_chbClick(nil);
    swarm_inertia_color_chb.checked:=readbool('swarm','inertia_color_ok',swarm_inertia_color_chb.checked);
    swarm_inertia_color_chbClick(nil);
    swarm_enemy_escape_color_chb.checked:=readbool('swarm','enemy_escape_color_ok',swarm_enemy_escape_color_chb.checked);
    swarm_enemy_escape_color_chbClick(nil);
    swarm_density_escape_color_chb.checked:=readbool('swarm','density_escape_color_ok',swarm_density_escape_color_chb.checked);
    swarm_density_escape_color_chbClick(nil);

    particle_rotation_speed_sb.position:=readinteger('particle','rotation_speed',particle_rotation_speed_sb.position);
    particle_rotation_speed_sbChange(nil);
    particle_center_speed_sb.position:=readinteger('particle','center_speed',particle_center_speed_sb.position);
    particle_center_speed_sbChange(nil);
    particle_inertia_sb.position:=readinteger('particle','inertia',particle_inertia_sb.position);
    particle_inertia_sbChange(nil);
    particle_random_sb.position:=readinteger('particle','random',particle_random_sb.position);
    particle_random_sbChange(nil);
    particle_synch_sb.position:=readinteger('particle','synch',particle_synch_sb.position);
    particle_synch_sbChange(nil);

    density_raster_chb.checked:=readbool('density','raster',density_raster_chb.checked);
    density_raster_radius_sb.position:=readinteger('density','raster_radius',density_raster_radius_sb.position);
    density_raster_radius_sbchange(nil);
    density_allowed_se.value:=readinteger('density','allowed',density_allowed_se.value);
    density_allowed_sechange(nil);
    density_escape_steps_sb.position:=readinteger('density','escape_steps',density_escape_steps_sb.position);
    density_escape_steps_sbchange(nil);
    density_escape_speed_sb.position:=readinteger('density','escape_speed',density_escape_speed_sb.position);
    density_escape_speed_sbchange(nil);

    enemy_escape_viewer_chb.checked:=readbool('enemy_escape','viewer_ok',enemy_escape_viewer_chb.checked);
    enemy_escape_viewer_chbClick(nil);
    enemy_escape_distance_sb.position:=readinteger('enemy_escape','distance',enemy_escape_distance_sb.position);
    enemy_escape_distance_sbChange(nil);
    enemy_escape_steps_sb.position:=readinteger('enemy_escape','steps',enemy_escape_steps_sb.position);
    enemy_escape_steps_sbchange(nil);
    enemy_escape_speed_sb.position:=readinteger('enemy_escape','speed',enemy_escape_speed_sb.position);
    enemy_escape_speed_sbchange(nil);

    free;
  end;

  self.WindowState:=wsmaximized;
  FormResize(Sender);
  activecontrol:=nil;
  model_frequency_t.enabled:=true;
end;

//clear program-------------------------------------------------------
procedure Tmain_f.FormDestroy(Sender: TObject);
var
  r:integer;
begin
  model_frequency_t.enabled:=false;

  deletefile(home_dir+_ini_fn);
  with tinifile.create(home_dir+_ini_fn) do
  begin
    writeinteger('param','activepageindex',pctrl.ActivePageIndex);

    writeinteger('model','freqency',model_frequency_sb.Position);
    writebool('model','background_ok',model_background_chb.checked);

    writeinteger('navigation','speed',navigation_speed_sb.Position);

    writeinteger('swarm','particles',swarm_particles_sb.position);
    writebool('swarm','filled_ok',swarm_filled_chb.checked);
    writebool('swarm','colored_ok',swarm_colored_chb.checked);
    writebool('swarm','enemy_inertia_color_ok',swarm_inertia_color_chb.checked);
    writebool('swarm','enemy_escape_color_ok',swarm_enemy_escape_color_chb.checked);
    writebool('swarm','density_escape_color_ok',swarm_density_escape_color_chb.checked);

    writeinteger('particle','rotation_speed',particle_rotation_speed_sb.position);
    writeinteger('particle','center_speed',particle_center_speed_sb.position);
    writeinteger('particle','inertia',particle_inertia_sb.position);
    writeinteger('particle','random',particle_random_sb.position);
    writeinteger('particle','synch',particle_synch_sb.position);

    writeinteger('enemy_escape','enemy_escape_distance',enemy_escape_distance_sb.position);
    writeinteger('enemy_escape','enemy_escape_steps',enemy_escape_steps_sb.position);
    writeinteger('enemy_escape','enemy_escape_speed',enemy_escape_speed_sb.position);

    writebool('density','raster',density_raster_chb.checked);
    writeinteger('density','raster_radius',density_raster_radius_sb.position);
    writeinteger('density','allowed',density_allowed_se.value);
    writeinteger('density','escape_steps',density_escape_steps_sb.position);
    writeinteger('density','escape_speed',density_escape_speed_sb.position);

    writebool('enemy_escape','viewer_ok',enemy_escape_viewer_chb.checked);
    writeinteger('enemy_escape','distance',enemy_escape_distance_sb.position);
    writeinteger('enemy_escape','steps',enemy_escape_steps_sb.position);
    writeinteger('enemy_escape','speed',enemy_escape_speed_sb.position);

    free;
  end;

  //free textures
  glDeleteTextures(1,@bullet_tx);
  glDeleteTextures(1,@model_background_tx);
  gluDeleteQuadric(model_background_quad);

  //free ogl-objects
  for r:=0 to _bullet_max-1 do gluDeleteQuadric(bullet_a[r].quad);
  for r:=0 to _particle_max-1 do particle_a[r].Free;

  //free opengl environment
  DeactivateRenderingContext;
  DestroyRenderingContext(handle_RC);
  ReleaseDC(view_p.Handle,handle_DC);
end;

//--------------------------------------------------
procedure Tmain_f.FormKeyDown(
  Sender: TObject;
  var Key:Word;
  Shift:TShiftState
);
begin
  if key=vk_escape then
  begin
    close;
    exit;
  end;

  if ssctrl in shift then
  begin
    if      key=ord('1') then my_pos_v.x:=my_pos_v.x-0.1
    else if key=ord('2') then my_pos_v.y:=my_pos_v.y-0.1
    else if key=ord('3') then my_pos_v.z:=my_pos_v.z-0.1;
  end
  else
  begin
    if key=vk_f1 then
    begin
      my_pos_v:=v_fill(0,0,0);
      my_rot_v:=v_fill(0,0,0);
    end
    else if key=ord('1') then my_pos_v.x:=my_pos_v.x+0.1
    else if key=ord('2') then my_pos_v.y:=my_pos_v.y+0.1
    else if key=ord('3') then my_pos_v.z:=my_pos_v.z+0.1;
  end;

  active_key:=0;

  //shift & ctrl state
  active_ctrl:=(ssctrl in shift);

  //flight key pressed?
  if
    (key=vk_up)or
    (key=vk_down)or
    (key=vk_left)or
    (key=vk_right)or
    (key=vk_space)
  then begin
    active_key:=key;
    key:=0;
    exit;
  end;
end;

//set key holder back-----------------------------------------------------
procedure Tmain_f.FormKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  active_key:=0;
  active_ctrl:=false;
end;

//------------------------------------------------------------
//FUNCTIONS
//------------------------------------------------------------

//return textur-pointer from image-memory-datas --------------------
function tmain_f.CreateTexture(Width,Height:Word;pData:Pointer):Integer;
var
  Texture:TGLuint;
begin
  glGenTextures(1,@Texture);
  glBindTexture(GL_TEXTURE_2D,Texture);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);

  gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,Width,Height,GL_RGBA,GL_UNSIGNED_BYTE,pData);
  result:=Texture;
end;

//--------------------------------------------------------------
//return textur-pointer from timage
function tmain_f.img2tx(img:timage):TGLuint;
var
  data:Array of LongWord;
  w,x:integer;
  h,y:integer;
  bmp:tbitmap;
  c:longword;
  line:^longword;
begin
  bmp:=TBitmap.Create;
  bmp.Assign(img.Picture.Graphic);

  //ogl braucht 32bit-pics
  bmp.PixelFormat:=pf32bit;
  w:=bmp.width;
  h:=bmp.height;
  SetLength(data,w*h);

  for y:=0 to h-1 do
  begin
    line:=bmp.scanline[h-y-1];
    for x:=0 to w-1 do begin
      c:=line^ and $FFFFFF; // Need to do a color swap
      data[x+(y*w)]:=(((c and $FF)shl 16)+(c shr 16)+(c and $FF00)) or $FF000000;
      inc(line);
    end;
  end;

  BMP.free;
  result:=CreateTexture(w,h,addr(Data[0]));
end;

//--------------------------------------------------------------
procedure Tmain_f.FormResize(Sender: TObject);
begin
  //ogl-adaptionen
  glViewport(0,0,view_p.ClientWidth,view_p.ClientHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity;
  gluPerspective(50,view_p.ClientWidth/view_p.ClientHeight,_NearClipping,_FarClipping);
  glMatrixMode(GL_MODELVIEW);
  Draw_Scene;

  status_p.width:=view_p.width-(view_p.width div 4);
  status_p.Left:=(view_p.width-status_p.width) div 2
end;

procedure Tmain_f.model_frequency_sbChange(Sender: TObject);
begin
  model_frequency_t.Interval:=model_frequency_sb.max-model_frequency_sb.Position+1;
end;

procedure Tmain_f.view_pClick(Sender: TObject);
begin
  activecontrol:=nil;
end;

procedure Tmain_f.navigation_speed_sbChange(Sender: TObject);
begin
  my_pos_speed_delta:=navigation_speed_sb.position/100;
end;

procedure Tmain_f.density_allowed_seChange(Sender: TObject);
begin
  try density_allowed_max:=density_allowed_se.value;except end;
end;

procedure Tmain_f.enemy_escape_viewer_chbClick(Sender: TObject);
begin
  enemy_escape_viewer_ok:=enemy_escape_viewer_chb.checked;
end;

procedure Tmain_f.swarm_density_escape_color_chbClick(Sender: TObject);
begin
  swarm_density_escape_color_ok:=swarm_density_escape_color_chb.checked;
end;

procedure Tmain_f.swarm_enemy_escape_color_chbClick(Sender: TObject);
begin
  swarm_enemy_escape_color_ok:=swarm_enemy_escape_color_chb.checked;
end;

//------------------------------------------------------------------
procedure Tmain_f.model_frequency_tTimer(Sender: TObject);

  //--------------------------------------------------------------
  //give back rotated look vector about all axis
  function my_look_vector_get:tv;
  var
    v:tv;
    mx,my,mz,m:tm;
  begin
    //fill roation matrices
    mx:=m_fill_rot_x_deg(360-my_rot_v.x);
    my:=m_fill_rot_y_deg(360-my_rot_v.y);
    mz:=m_fill_rot_z_deg(360-my_rot_v.z);
    //create general rotation matrice
    m:=m_mul(mz,my);
    m:=m_mul(m,mx);
    //rotate the look vector about all axis
    v:=v_fill(0,0,-1);
    v:=m_v_mul(m,v);
    result:=v;
  end;

  //--------------------------------------------------------------
  procedure my_pos_calc(dir:integer);
  begin
    my_look_v:=my_look_vector_get;
    my_pos_v.x:=my_pos_v.x+my_look_v.x*dir*my_pos_speed_delta;
    my_pos_v.y:=my_pos_v.y+my_look_v.y*dir*my_pos_speed_delta;
    my_pos_v.z:=my_pos_v.z+my_look_v.z*dir*my_pos_speed_delta;
  end;

  //--------------------------------------------------------------
  procedure my_rotation_calc(dir:integer;axis:byte);
  begin
    if axis=0 then my_rot_v.x:=deg_norm(my_rot_v.x-dir*_my_rot_delta);
    if axis=1 then my_rot_v.y:=deg_norm(my_rot_v.y-dir*_my_rot_delta);
    if axis=2 then my_rot_v.z:=deg_norm(my_rot_v.z-dir*_my_rot_delta);
  end;

var
  r:integer;
begin
  //change position/direction?
  if active_key<>0 then
  begin
    if active_ctrl then
    begin
      //rotation x-axis
      if      active_key=vk_up    then my_rotation_calc(-1,0)
      else if active_key=vk_down  then my_rotation_calc( 1,0);
      //rotation z-axis
      if      active_key=vk_left  then my_rotation_calc(-1,2)
      else if active_key=vk_right then my_rotation_calc( 1,2);
    end
    else
    begin
      //flying: rotation y-axis
      if      active_key=vk_right then my_rotation_calc(-1,1)
      else if active_key=vk_left  then my_rotation_calc( 1,1)
      //movement forward or backward
      else if active_key=vk_up   then my_pos_calc( 1)
      else if active_key=vk_down then my_pos_calc(-1);
    end;

    if active_key=vk_space then
    begin
      //schuss frei?
      for r:=0 to _bullet_max-1 do
      begin
        if bullet_a[r].count>0 then continue;
        bullet_a[r].pos_v:=my_pos_v;
        bullet_a[r].count:=50;
        bullet_a[r].dir_v:=my_look_vector_get;
        break;
      end;
      active_key:=0;
    end;
  end;
  draw_scene;
end;

//-------------------------------------------------
function tmain_f.intto1000er(l:extended):string;
begin
  result:=format('%.0n',[l]);
end;

//-------------------------------------------------
function tmain_f.float_to_string(d:single):string;
begin
  result:=format('%.2f',[d]);
end;

//-------------------------------------------------
function tmain_f.float_to_string(d:single;dec:byte):string;
begin
  result:=format('%.'+inttostr(dec)+'f',[d]);
end;

procedure Tmain_f.particle_rotation_speed_sbChange(Sender: TObject);
begin
  particle_rotation_speed:=particle_rotation_speed_sb.position;
  particle_rotation_speed:=(particle_rotation_speed*particle_rotation_speed)/1000000;
end;

procedure Tmain_f.particle_center_speed_sbChange(Sender: TObject);
begin
  particle_center_speed:=particle_center_speed_sb.position;
  particle_center_speed:=(particle_center_speed*particle_center_speed)/1000000;
end;

procedure Tmain_f.swarm_particles_sbChange(Sender: TObject);
begin
  swarm_particles:=swarm_particles_sb.position;
end;

procedure Tmain_f.enemy_escape_distance_sbChange(Sender: TObject);
begin
  enemy_escape_distance:=enemy_escape_distance_sb.position/10;
end;

procedure Tmain_f.enemy_escape_steps_sbChange(Sender: TObject);
begin
  enemy_escape_steps:=enemy_escape_steps_sb.position;
end;

procedure Tmain_f.enemy_escape_speed_sbChange(Sender: TObject);
begin
  enemy_escape_speed:=enemy_escape_speed_sb.position;
end;

procedure Tmain_f.density_escape_steps_sbChange(Sender: TObject);
begin
  density_escape_steps:=density_escape_steps_sb.position;
end;

procedure Tmain_f.density_escape_speed_sbChange(Sender: TObject);
begin
  density_escape_speed:=density_escape_speed_sb.position/100;
  density_escape_speed:=density_escape_speed*density_escape_speed;
end;

//------------------------------------------------------------------
procedure tmain_f.draw_scene;

  //model_background-------------------------------------------------
  procedure draw_model_background;
  begin
    glPushMatrix();
      gldisable(GL_DEPTH_TEST);
      glTranslatef(0,0,0);
      glRotatef(90,1,0,0);
      glenable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,model_background_tx);
      gluSphere(model_background_quad,_model_background_radius,100,100);
      glColor3f(1,1,1);
      glDisable(GL_TEXTURE_2D);
      glenable(GL_DEPTH_TEST);
    glPopMatrix();
  end;

  //----------------------------------------------------
  procedure draw_bullets;
  var
    r:integer;
    v:tv;
  begin
    glPushMatrix();
    glTranslatef(0,0,0);
    glenable(GL_DEPTH_TEST);
    for r:=0 to _bullet_max-1 do
    begin
      if bullet_a[r].count<=0 then continue;
      bullet_a[r].count:=bullet_a[r].count-1;
      glColor3f(1,0.4,0.4);

      v:=bullet_a[r].dir_v;
      v:=v_norm(v);

      //adapt speed of change
      v:=v_scale(v,-1);

      //calculate new position
      bullet_a[r].pos_v:=v_sub(bullet_a[r].pos_v,v);

      glColor3f(1,1,1);
      glTranslatef(bullet_a[r].pos_v.x,bullet_a[r].pos_v.y,bullet_a[r].pos_v.z);
      glenable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,bullet_tx);
      gluSphere(bullet_a[r].quad,enemy_escape_distance/4,10,10);
      //glColor3f(1,1,1);
      glDisable(GL_TEXTURE_2D);
    end;
    glPopMatrix();
  end;

  //-------------------------------------------------
  procedure draw_density_raster;

    procedure draw_it;
    var
      x,y,z:integer;
    begin
      for z:=-density_raster_radius to density_raster_radius do
      begin
        for x:=-density_raster_radius to density_raster_radius do
        begin
          glBegin(GL_LINE_LOOP);
          glVertex3f(x*_raster_cell_dim,-density_raster_radius*_raster_cell_dim,z*_raster_cell_dim);
          glVertex3f(x*_raster_cell_dim, density_raster_radius*_raster_cell_dim,z*_raster_cell_dim);
          glEnd();
        end;
        for y:=-density_raster_radius to density_raster_radius do
        begin
          glBegin(GL_LINE_LOOP);
          glVertex3f(-density_raster_radius*_raster_cell_dim,y*_raster_cell_dim,z*_raster_cell_dim);
          glVertex3f( density_raster_radius*_raster_cell_dim,y*_raster_cell_dim,z*_raster_cell_dim);
          glEnd();
        end;
      end;
    end;

  begin
    glPushMatrix();
    glColor3f(1,0,0);
    draw_it;
    glrotatef(90,1,0,0);
    draw_it;
    glPopMatrix();
  end;

  //-----------------------------------------
  procedure draw_particles;
  var
    r:integer;
    x,y,z:integer;
  begin
    //rasteritter leeren
    enemy_escape_count:=0;
    density_escape_count:=0;
    density_max:=0;
    test_d:=0;

    //raster_density_c:=0;
    swarm_radius_max:=0;
    for z:=-main_f.density_raster_radius to main_f.density_raster_radius do
      for y:=-main_f.density_raster_radius to main_f.density_raster_radius do
        for x:=-main_f.density_raster_radius to main_f.density_raster_radius do
        begin
          raster_a[x,y,z].count:=0;
          raster_a[x,y,z].dir_v:=v_fill(0,0,0);
        end;

    //schwarm-partikel malen
    glPushMatrix();
    glenable(GL_DEPTH_TEST);
    glColor3f(0.8,0.8,1);
    if random(2)=0 then
    begin
      for r:=0 to swarm_particles-1 do particle_a[r].draw;
    end
    else
    begin
      for r:=swarm_particles-1 downto 0 do particle_a[r].draw;
    end;
    glenable(GL_DEPTH_TEST);
    glPopMatrix();
  end;

begin
  model_frequency_t.Enabled:=false;
  if
    not(activecontrol is tspinedit)and
    not(activecontrol is tcheckbox)
  then activecontrol:=nil;
  //if not(activecontrol is tspinedit) then activecontrol:=nil;

  //get graphic mode
  if swarm_filled_ok then glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
                     else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glClear(GL_COLOR_BUFFER_BIT OR GL_DEPTH_BUFFER_BIT);
  glLoadIdentity;


  //rotation & positioning
  model_rotation_v.x:=deg_norm(my_rot_v.x);
  model_rotation_v.y:=deg_norm(my_rot_v.y);
  model_rotation_v.z:=deg_norm(my_rot_v.z);

  glRotatef(model_rotation_v.x,1.0,0,0);
  glRotatef(model_rotation_v.y,0,1.0,0);
  glRotatef(model_rotation_v.z,0,0,1.0);

  glTranslatef(-my_pos_v.x,-my_pos_v.y,-my_pos_v.z);


  if model_background_ok then draw_model_background;
  if density_raster_chb.checked then draw_density_raster;
  draw_bullets;
  draw_particles;

  //nötig, damit model-background sichtbar
  glColor3f(1,1,1);

  main_f.Tag:=1;
  SwapBuffers(handle_DC);

  if pctrl.activepage=navigation_ts then
  begin
    navigation_pos_x_e.Text:=float_to_string(my_pos_v.x);
    navigation_pos_y_e.Text:=float_to_string(my_pos_v.y);
    navigation_pos_z_e.Text:=float_to_string(my_pos_v.z);
    navigation_rot_x_e.Text:=float_to_string(my_rot_v.x);
    navigation_rot_y_e.Text:=float_to_string(my_rot_v.y);
    navigation_rot_z_e.Text:=float_to_string(my_rot_v.z);
  end
  else
  if pctrl.activepage=swarm_ts then
  begin
    swarm_radius_e.text:=float_to_string(swarm_radius_max);
  end
  else
  if pctrl.activepage=density_escape_ts then
  begin
    density_max_e.Text:=inttostr(density_max);
    density_escape_e.Text:=inttostr(density_escape_count);
  end
  else
  if pctrl.activepage=enemy_escape_ts then
  begin
    enemy_escape_e.Text:=inttostr(enemy_escape_count);
  end;

  model_frequency_t.Enabled:=true;
end;

procedure Tmain_f.particle_random_sbChange(Sender: TObject);
begin
  particle_random:=particle_random_sb.position;
end;

procedure Tmain_f.model_background_chbClick(Sender: TObject);
begin
  model_background_ok:=model_background_chb.checked;
end;

procedure Tmain_f.swarm_colored_chbClick(Sender: TObject);
begin
  swarm_colored_ok:=swarm_colored_chb.checked;
end;

procedure Tmain_f.swarm_filled_chbClick(Sender: TObject);
begin
  swarm_filled_ok:=swarm_filled_chb.checked;
end;

procedure Tmain_f.particle_inertia_sbChange(Sender: TObject);
begin
  particle_inertia:=particle_inertia_sb.position;
end;

procedure Tmain_f.swarm_inertia_color_chbClick(Sender: TObject);
begin
  swarm_inertia_color_ok:=swarm_inertia_color_chb.checked;
end;

procedure Tmain_f.particle_synch_sbChange(Sender: TObject);
begin
  particle_synch:=particle_synch_sb.position;
end;

procedure Tmain_f.sbScroll(Sender: TObject; ScrollCode: TScrollCode; var ScrollPos: Integer);
var
  sb:tscrollbar;
begin
  sb:=tscrollbar(sender);
  status_p.caption:=sb.hint+': '+intto1000er(sb.position)+' / '+intto1000er(sb.max);
  status_p.visible:=true;
  if scrollcode<>scEndScroll then exit;
  status_p.visible:=false;
end;

procedure Tmain_f.density_raster_radius_sbChange(Sender: TObject);
begin
  density_raster_radius:=density_raster_radius_sb.position;
end;

end.

