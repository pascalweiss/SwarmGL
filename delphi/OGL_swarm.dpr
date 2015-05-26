program OGL_swarm;

uses
  Forms,
  main_u in 'main_u.pas' {main_f},
  dan_geo_u in 'dan_geo_u.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(Tmain_f, main_f);
  Application.Run;
end.
