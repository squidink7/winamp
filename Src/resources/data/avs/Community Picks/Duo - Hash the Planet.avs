Nullsoft AVS Preset 0.2         ______________________________________________________

Whacko Revisited
Hash the Planet
Remix by: Duo

Original: Groovy Saturn
______________________________________________________
������������������������������������������������������
 ����c  � $�   �                         @  AVS 2.8+ Effect List Config                    $   �   j   x=0;
y=i-.5;
red=v*8-sin(i*20-t)*8-sx;
green=cos(i*200+cx)-v*8+cx;
blue=getosc(v,0,0)*20+cos(t*.5);
 '   t=t+.05;sx=gmegabuf(1);cx=gmegabuf(2);    t=0;    n=100       ���       D   �  '   sf=gmegabuf(7);
d=if(above(d,.3),0,d)                    �q�Color Map                       @           �        p��                                                      ��L                                                      h�                                                      ��c                                                      H�R                                                      ��                                                      ���                                                      (Nb                                                            �    �� \  �   ���                �   ��  zk  �   ���                {   � � �  �    �� 2Y  �   ���                _   ��  �  �   ���                \   Eڵ >  �   ���                h    �� �e  �    �� R+  �   ���                Z   ��� �N  �   �E *  �   ���                O    �  u  �   ��  ]  �   ���    +   Y      z=.8+sf*1.25;
x=x*z;
y=y*z; 
   sf=reg06;                                     ,          ,                            �                
   �                                                                           �����  � $�   �                           @  AVS 2.8+ Effect List Config                    $   X  m  px=sd1/262144-0.125;
py=cos(ang)*rad;
pz=sin(ang)*rad;
ssd1=(sd1*0.83 + sd2*2.29 + 3491) % 65536;
sd2=(sd2*0.89 + sd3*1.49 + 4177) % 65536;
sd3=(sd3*1.79 + sd1*0.73) % 65536;
sd1=ssd1;rad=sd2/65536+1.2;ang=i*6.28+(sd3%10/10)*t;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+2.5;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
dc=band(below(x*x+y*y,0.2),above(z3,2.35));
y=y*af;cf=abs(v)*3+.5;
red=if(dc,0,1-v);green=if(dc,0,1);blue=if(dc,0,1);
x=x*sf;y=y*sf; }   rp=0;mp=1;cv=0;sd1=45239;sd2=6541;sd3=8992;t=t+0.05;
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;af=w/h;    // ring E   n=300;ry=1.57;rx=0;rz=1.57;rxo=0.019;ryo=-0.03;rzo=-0.023;t=0;sf=1.2       ���     l��Holden03: Convolution Filter    �                                                                                                                                                                                                                        (       �$   �     // global shit �   rx=rx+rxo-(rx*.05);ry=ry+ryo;rz=rz+rzo;cx=cos(rx);sx=sin(rx);cy=cos(ry);sy=sin(ry);cz=cos(rz);sz=sin(rz);sf=sf+bf-(sf*.2);
reg00=cx;reg01=sx;reg02=cy;reg03=sy;reg04=cz;reg05=sz;reg06=sf; d   rxo=rand(50)/200;
ryo=rand(10)/100*.7-.025;
rzo=rand(10)/100*.9-.025;
bf=(rand(50)/100)*.35+.05; d   ry=1.57;rx=0;rz=1.57;rxo=0.019;ryo=-0.03;rzo=-0.023;t=0;sf=1.2;cx=0;sx=0;cy=0;sy=0;cz=0;sz=0;bf=.1;       ���    $   �  �  sd1=(sd1*411+911)%2000;
sd2=(sd2*1179+3791)%2000;
sd3=(sd3*3273+6541)%2000;
py=(sd3-1000)*.01;pz=(sd1-1000)*.01;px=(sd2-1000)*.01;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+1.5;

dt=if(above(z3,.001),1/z3,0);
x=if(dt,x3*dt,x);y=if(dt,y2*dt*af,y);
x=x*(1+sf*.3);
y=y*(1+sf*.3);
col=dt*(2.5+sf-getosc(sin(i*20)*20,0,0)*30);
red=col;
green=col;
blue=col; �   cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
;x=0;y=0;af=w/h;t=t+ti*.01;ti=ti*.8;bf=bf*.9+bft*.1;sd1=414;sd2=711;sd3=414 �   ti=5;bft=getosc(0.7,0,0);sbo=if(sbo+getosc(.79,0,0)*100%10,sbo,6.28);sbs=if(equal(sbo,6.28),(getosc(.1,0,0)*256%2)*2-1,sbs);li=1;
// bg stars    n=400;tpi=acos(-1)*2;        ���     $   g  p  pg=1-sf*.2;
pz=pg*cos(i*$pi*2+fr);
px=0;
py=pg*sin(i*$pi*2+fr);
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+1.5;
x=x3/z3;
y=y2/z3;
c=gmegabuf(1);
adc=if(below(c,z3-1.9),0,1)*sin(i*20)*.2;
dc=if(above(abs(z3*.1),.2),0,1)*fr*sin(i*20-fr-sf*8)*2;
red=dc;
green=dc;
blue=dc;
x=x*(.5+sf*.7);y=y*(.5+sf*.7)*af; l   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.3);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h;    bt=rand(10)/100;
// ring P   n=80;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2;
       ���    �q�Color Map                       @      	      \        ���
                                                      �J�
                                                      0J�
                                                      hJ�
                                                      �J�
                                                       }b                                                      ��!                                                      �g                                                            �    �� \  �   ���                �   ��  zk  �   ���                {   � � �  �    �� 2Y  �   ���                _   ��  �  �   ���                W    �  >  �   ��� �              {    �� �e  �    �� R+  �   ���                Z   ��� �N  �   �E *  �   ���                S   4J~ u  l   ¦! I  �   ���    l��Holden03: Convolution Filter    �                                                                                                                                                                                                            $   �  �  red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57);
py=cos(rp/nc*6.28)*rad;pz=sin(rp/nc*6.28)*rad;px=sin(mp*1.57);
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+2.5;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
dc=above(z3,2.2);
red=if(dc,0,red);green=if(dc,0,green);blue=if(dc,0,blue);
x=x*sf;y=y*sf;
linesize=sf*2; [   rp=0;mp=-1;cv=0;
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h;    // planet 1 N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   �  �  red=cr;green=cg;blue=cb;
cr=1-cv;cg=1-cv;cb=1-cv;
rad=1;
px=cos(rp/nc*6.28)*rad;py=sin(rp/nc*6.28)*rad;pz=0;
y0=py*cos(mp*3.14);z0=py*sin(mp*3.14);
x1=px*cz+y0*sz;y1=y0*cz-px*sz;
y2=y1*cx+z0*sx;z2=z0*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+2.5;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
dc=above(z3,2.2);
red=if(dc,0,red);green=if(dc,0,green);blue=if(dc,0,blue);
x=x*sf;y=y*sf;
 j   rp=0;mp=-1;cv=0;cr=1;cg=1;cb=1;
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h;    // planet 2 M   n=261;nc=50;nm=.2;ry=1.57;rx=0;rz=1.57;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   �   b   x=cos(i*6.28)*0.44;
y=sin(i*6.28)*0.44*af;
x=x*sf;y=y*sf;
c=(x*x+y*y);
assign(gmegabuf(1),c);    sf=reg06;af=w/h;    // outline    n=40;sf=1.2       ���    $   0    red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57); cs=.4+getosc(cb,0,0)*.075;
px=cs*(cos(rp/nc*6.28)*rad)-fc*2;
py=cs*(sin(rp/nc*6.28)*rad)+2.5;
pz=cs*(sin(mp*1.57))+fs*2;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+4;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
c=gmegabuf(1);
dc=-if(above(c,z3-5),0,1)+z3*.1;
red=dc;
green=dc;
blue=dc;
x=x*sf;y=y*sf; �   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.1);fc=cos(fr);fs=sin(fr);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h; !   // satellite 1
bt=rand(50)/100; N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   /    red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57); cs=.2+getosc(cb,0,0)*.05;
px=cs*(cos(rp/nc*6.28)*rad)-fs*2;
py=cs*(sin(rp/nc*6.28)*rad)+2.5;
pz=cs*(sin(mp*1.57))+fc*2;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+4;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
c=gmegabuf(1);
dc=-if(above(c,z3-5),0,1)+z3*.1;
red=dc;
green=dc;
blue=dc;
x=x*sf;y=y*sf; �   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.1);fc=cos(fr);fs=sin(fr);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h; !   // satellite 2
bt=rand(50)/100; N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   ,    red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57); cs=.15+getosc(cb,0,0)*.1;
pz=cs*(cos(rp/nc*6.28)*rad)-fs;
px=cs*(sin(rp/nc*6.28)*rad)-2.5;
py=cs*(sin(mp*1.57))+fc;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+4;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
c=gmegabuf(1);
dc=-if(above(c,z3-5),0,1)+z3*.1;
red=dc;
green=dc;
blue=dc;
x=x*sf;y=y*sf; �   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.15);fc=cos(fr);fs=sin(fr);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h; !   // satellite 3
bt=rand(50)/100; N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   1    red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57); cs=.085+getosc(cb,0,0)*.3;
py=cs*(cos(rp/nc*6.28)*rad)+fs*2;
pz=cs*(sin(rp/nc*6.28)*rad)-2.5;
px=cs*(sin(mp*1.57))-fc*2;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+4;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
c=gmegabuf(1);
dc=-if(above(c,z3-5),0,1)+z3*.1;
red=dc;
green=dc;
blue=dc;
x=x*sf;y=y*sf; �   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.15);fc=cos(fr);fs=sin(fr);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h; !   // satellite 4
bt=rand(50)/100; N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���    $   2    red=cr;green=cr;blue=cr;
cr=1-cv;cg=11-cv;cb=1-cv;
rad=cos(mp*1.57); cs=.1+getosc(cb,0,0)*.35;
py=cs*(cos(rp/nc*6.28)*rad)+fc;
px=cs*(sin(rp/nc*6.28)*rad)+max(2,fr);
pz=cs*(sin(mp*1.57))-fs;
x1=px*cz+py*sz;y1=py*cz-px*sz;
y2=y1*cx+pz*sx;z2=pz*cx-y1*sx;
x3=x1*cy+z2*sy;z3=z2*cy-x1*sy+4;
x=if(above(z3,0.1),x3/z3,x);y=if(above(z3,0.1),y2/z3*af,y);
rp=if(equal(cv,0),(rp+1)%nc,rp);
mp=if(equal(cv,0),mp,mp+nm);
cv=if(equal(rp,0),1-cv,0);
c=gmegabuf(1);
dc=-if(above(c,z3-4),0,1)+z3*.1;
red=dc;
green=dc;
blue=dc;
x=x*sf;y=y*sf; �   rp=0;mp=-1;cv=0;fr=fr+bt-(fr*.15);fc=cos(fr);fs=sin(fr);
cx=reg00;sx=reg01;cy=reg02;sy=reg03;cz=reg04;sz=reg05;sf=reg06;
af=w/h; !   // satellite 5
bt=rand(50)/100; N   n=261;nc=25;nm=.2;ry=1.57;rx=0;rz=1.57;;rxo=0.019;ryo=-0.03;rzo=-0.023;sf=1.2       ���                           