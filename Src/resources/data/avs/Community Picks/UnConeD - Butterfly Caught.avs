						Nullsoft AVS Preset 0.2    z  v  
                    Butterfly Caught
by Steven Wittens aka UnConeD
						______________________________________________________
                        ����������������������������������������������������
						Some discussion on Winamp.com about a butteryfly preset and Tuggummi's awesome spectrum (which looks like grass at some times) inspired me to do this preset: a butterfly flying over a plain of grass.
						What (or who) is it looking for? I don't know ;).
						
						The grass is a neat extension of the idea in "Hello Light", except now the volumetric beams are perspective-correct and look much nicer. Basically the existing image is reverse projected and used as a blended texture on a new plane. By doing this 3 times, there are 2^3 = 8 copies made.
						
						The butterfly is a bunch of scopes with appropriate movement to look convincingly butterfly-ish. For minor response I added the color change and the moving dots on the wings.
						
						Finally, the grass also (slowly) changes between green (spring) and brown/yellow (autumn).
						
						The title is the name of a Massive Attack song which played while making this preset.
                        ____________________________________________________
						������������������������������������������������������
						(c) Steven Wittens / UnConeD
						steven @ acko dot net - www.acko.net
						
						If you wish to use any part (or the whole) of this preset in your own presets, packs or in another medium, you must include my name as a clear credit reference. Including my contact information/website address is not required, but appreciated.
						Exception to the above: you may display these presets as a projection at parties, raves or clubs without credit reference on-screen. $   �      p  t=t+0.01+ti;ti=ti*.9;
						p=t-.1;
						ox=cos(p)*cos(p*.179+1)+cos(sin(p*.141));
						oy=-1+sin(p*.15)*cos(-p*.71)*.3;
						oz=-(sin(p)*cos(-p*.41)+sin(cos(p*.631)))*1.5;
						ot=.5+.6/sqrt(sqr(ox)+sqr(oz));
						ox=ox*ot;oz=oz*ot;
						
						ry=atan2(ox,-oz);
						rx=-atan2(-oy-.2,sqrt(sqr(ox)+sqr(oz)));
						
						cx=cos(rx);sx=sin(rx);
						cy=cos(ry);sy=sin(ry);
						
						p=t;
						ox=cos(p)*cos(p*.179+1)+cos(sin(p*.141));
						oy=-.9+sin(p*.15)*cos(-p*.71)*.4;
						oz=-(sin(p)*cos(-p*.41)+sin(cos(p*.631)))*1.5;
						ot=.5+.6/sqrt(sqr(ox)+sqr(oz));
						ox=ox*ot;oz=oz*ot;
						
						reg00=ox;reg01=oy;reg02=oz;
						reg03=rx;reg04=ry;
						reg10=cx;reg11=sx;
						reg12=cy;reg13=sy;
						reg20=w/h;reg21=h/w;
						    ti=.1*getspec(0,.3,0);    n=0;// Camera global       ���     �����  �  $�   �                           @  AVS 2.8+ Effect List Config                    $     �   x=rand(1000)*.002-1;
						y=rand(1000)*.002-1;
						
						cv1=sqr(rand(100)*.01);cv2=rand(100)*.01;
						green=cv1*.9+.1;red=cv2*.2+green*(.4+sin(t)*.4);blue=.05;
						if(rand(100),0,assign(red,rand(100)*.01)); "   n=if(e,50000,200);
						e=0;t=t+.005;        e=1;// Grass
						t=5;       ���                       �            ��z             +   m  �   dy=y*iaf;
						dy2=dy*cx-sx;dz2=dy*sx+cx;
						dx3=x*cy-dz2*sy;dz3=x*sy+dz2*cy;
						
						k=-oy/dy2;
						ix=ox+dx3*k;iy=oy+dy2*k;iz=oz+dz3*k;
						x=(ix+reg18)*.5;y=(iz+reg19)*.5;
						alpha=max(0,min(1,1.8-k*.5))*above(k,0);
						 m   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						af=reg20;iaf=reg21;        t=0;                                    +   �  =  // Raytrace
						dy=y*iaf;
						dy2=dy*cx-sx;dz2=dy*sx+cx;
						dx3=x*cy-dz2*sy;dz3=x*sy+dz2*cy;
						
						k=-oy/dy2;
						
						// Project into world
						px=dx3*k;py=dy2*k+.025;pz=dz3*k;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						alpha=above(k,0)*.5; m   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						af=reg20;iaf=reg21;        t=0;                            +   �  <  // Raytrace
						dy=y*iaf;
						dy2=dy*cx-sx;dz2=dy*sx+cx;
						dx3=x*cy-dz2*sy;dz3=x*sy+dz2*cy;
						
						k=-oy/dy2;
						
						// Project into world
						px=dx3*k;py=dy2*k+.05;pz=dz3*k;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						alpha=above(k,0)*.5; m   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						af=reg20;iaf=reg21;        t=0;                            +   �  ;  // Raytrace
						dy=y*iaf;
						dy2=dy*cx-sx;dz2=dy*sx+cx;
						dx3=x*cy-dz2*sy;dz3=x*sy+dz2*cy;
						
						k=-oy/dy2;
						
						// Project into world
						px=dx3*k;py=dy2*k+.1;pz=dz3*k;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						alpha=above(k,0)*.5; m   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						af=reg20;iaf=reg21;        t=0;                            $   P      T  ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						try=try+sin(min(2,abs(ry-lry))*sign(ry-lry)-try)*.2;
						t=t+.7+vb*.12;cry=sin(t);dt=dt+.1+dti;dti=dti*.9;
						dry=ry+sin(t*.05+sin(t*.13))*.2+try;
						vert=vert*.5+.5*(1-abs(sin(t*.25)));
						dz=dz*.9+dst*.1;vb=vb*.9;tt=tt-tti;tti=tti*.9+getspec(0,.1,0)*.15;
						
						lry=ry;
						vvb=vvb*.8+vb*.5;
						reg32=cry;reg33=dry;reg34=vert-vvb+1;reg35=dz;reg36=tt;
						reg37=sin(hu)*.5+.9;reg38=sin(hu+2.09)*.5+.5;reg39=sin(hu+4.18)*.4+.2;
						reg38=sqr(reg38);
						hu=hu+.02;
						
						vx=vx*.9+(tx-bcx)*.1;bcx=bcx+vx*.1;
						vy=vy*.9+(ty-bcy)*.1;bcy=bcy+vy*.1;
						reg40=bcx*3;reg41=bcy; �   dst=rand(100)*.04+1;dti=rand(100)*.01;vb=rand(100)*.01;
						hu=hu+rand(628)*.01;
						tx=(rand(200)*.01-1)*min(1,getspec(0,.5,0)*3);
						ty=(rand(200)*.01-1)*min(1,getspec(0,.5,0)*3); -   n=0;// Butterfly calculations
						dz=1;dst=1.5;       ���     $   �  b  u=i;
						// Wing shape
						i=i*4.35;
						u1=below(i,1);c=bnot(u1);u2=c*below(i,2);c=c*bnot(u2);
						u3=c*below(i,3);c=c*bnot(u3);u4=c*below(i,4);c=c*bnot(u4);u5=c;
						i=i-u2-u3*2-u4*3-u5*4;si=sqr(i);
						px=u1*i+u2*(1+i*.1-si*.3)+u3*(.8+i*.5-si*.7)+u4*(.6-i*1.1+si*.5);
						py=-u1*(i*1.3-si*.5+.2)-u2*(1-i*1.1)-u3*(-i*.8-.1)+u4*(.9-i*.7)+u5*(.2-i*1.1);
						// Filling
						qx=if(ip,px,.05);qy=if(ip,py,0);qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*16*dt;
						cv=sqr(sin(u*$pi*8+reg36)*.5+.5)*.75+.25;
						red=reg37*cv+.5;green=reg38*cv+.2;blue=reg39*cv*.3;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=200; // Right wing filling
						        k�    $   �  e  u=i;
						// Wing shape
						i=i*4.35;
						u1=below(i,1);c=bnot(u1);u2=c*below(i,2);c=c*bnot(u2);
						u3=c*below(i,3);c=c*bnot(u3);u4=c*below(i,4);c=c*bnot(u4);u5=c;
						i=i-u2-u3*2-u4*3-u5*4;si=sqr(i);
						px=u1*i+u2*(1+i*.1-si*.3)+u3*(.8+i*.5-si*.7)+u4*(.6-i*1.1+si*.5);
						py=-u1*(i*1.3-si*.5+.2)-u2*(1-i*1.1)-u3*(-i*.8-.1)+u4*(.9-i*.7)+u5*(.2-i*1.1);
						// Filling
						qx=if(ip,-px,-.05);qy=if(ip,py,0);qz=0;
						// Flapping
						px=qx*ccy-qz*ssy;
						qz=-qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*16*dt;
						cv=sqr(sin(u*$pi*8+reg36)*.5+.5)*.75+.25;
						red=reg37*cv+.5;green=reg38*cv+.2;blue=reg39*cv*.3;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=200; // Left wing filling
						        k�    $   �  -  u=i;
						// Wing shape
						i=i*4.35;
						u1=below(i,1);c=bnot(u1);u2=c*below(i,2);c=c*bnot(u2);
						u3=c*below(i,3);c=c*bnot(u3);u4=c*below(i,4);c=c*bnot(u4);u5=c;
						i=i-u2-u3*2-u4*3-u5*4;si=sqr(i);
						px=u1*i+u2*(1+i*.1-si*.3)+u3*(.8+i*.5-si*.7)+u4*(.6-i*1.1+si*.5);
						py=-u1*(i*1.3-si*.5+.2)-u2*(1-i*1.1)-u3*(-i*.8-.1)+u4*(.9-i*.7)+u5*(.2-i*1.1);
						// Filling
						qx=px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=30; // Right wing Edge
						        k�    $   <  �  px=0;py=i-.4;
						// Filling
						qx=px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*12*dt;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=10; // Body
						        k�    $   �  /  u=i;
						// Wing shape
						i=i*4.35;
						u1=below(i,1);c=bnot(u1);u2=c*below(i,2);c=c*bnot(u2);
						u3=c*below(i,3);c=c*bnot(u3);u4=c*below(i,4);c=c*bnot(u4);u5=c;
						i=i-u2-u3*2-u4*3-u5*4;si=sqr(i);
						px=u1*i+u2*(1+i*.1-si*.3)+u3*(.8+i*.5-si*.7)+u4*(.6-i*1.1+si*.5);
						py=-u1*(i*1.3-si*.5+.2)-u2*(1-i*1.1)-u3*(-i*.8-.1)+u4*(.9-i*.7)+u5*(.2-i*1.1);
						// Filling
						qx=-px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy-qz*ssy;
						qz=-qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=30; // Left wing edge
						        k�    $   i    u=i;
						u=i*$pi*2;
						px=cos(u)*.15+.7;py=sin(u)*.15-.5;
						// Filling
						qx=px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=30; // Right wing 'Eye'        k�    $   �    u=i;
						u=i*$pi*2;
						px=cos(u)*.15*rd+.7;py=sin(u)*.15*rd-.5;
						// Filling
						qx=px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0; )  ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;
						
						rd=rd*.9+.1;    rd=.1; !   n=30; // Right wing 'Eye'
						rd=1;        k�    $   �    u=i;
						u=i*$pi*2;
						px=cos(u)*.15*rd+.5;py=sin(u)*.15*rd+.4;
						// Filling
						qx=px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy+qz*ssy;
						qz=qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0; )  ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;
						
						rd=rd*.9+.1;    rd=.1; !   n=30; // Right wing 'Eye'
						rd=1;        k�    $   j    u=i;
						u=i*$pi*2;
						px=cos(u)*.15+.7;py=sin(u)*.15-.5;
						// Filling
						qx=-px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy-qz*ssy;
						qz=-qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0;   ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;        n=30; // Left wing 'Eye'        k�    $   �    u=i;
						u=i*$pi*2;
						px=cos(u)*.15*rd+.7;py=sin(u)*.15*rd-.5;
						// Filling
						qx=-px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy-qz*ssy;
						qz=-qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0; )  ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;
						
						rd=rd*.9+.1;    rd=.1;     n=30; // Left wing 'Eye'
						rd=1;        k�    $   �    u=i;
						u=i*$pi*2;
						px=cos(u)*.15*rd+.5;py=sin(u)*.15*rd+.4;
						// Filling
						qx=-px*1.02;qy=py*1.05;qz=0;
						// Flapping
						px=qx*ccy-qz*ssy;
						qz=-qx*ssy-qz*ccy;
						// Tilt
						py=qy*.5-qz*.86+vert+.5;pz=-qy*.86-qz*.5+1+dz+reg41;px=px+reg40;
						// Orientation
						qx=px*dcy-pz*dsy;
						qz=px*dsy+pz*dcy;
						
						ip=bnot(ip);
						
						px=qx-ox;py=py-oy;pz=qz-oz;
						
						x1=px*cy+pz*sy;z1=-px*sy+pz*cy;
						y2=py*cx+z1*sx;z2=-py*sx+z1*cx;
						dt=if(above(z2,.01),1/z2,0);
						x=if(dt,x1*dt,x);y=if(dt,y2*dt*af,y);
						
						linesize=ls*2;
						cv=sqr(sin(u*$pi*8+t*.3)*.5+.5);
						red=0;green=0;blue=0; )  ox=reg00;oy=reg01;oz=reg02;
						rx=reg03;ry=reg04;rz=reg05;
						cx=reg10;sx=reg11;
						cy=reg12;sy=reg13;
						cry=reg32;dry=reg33;vert=reg34;dz=reg35;
						ccy=cos(cry);ssy=sin(cry);
						dcy=cos(dry);dsy=sin(dry);
						
						af=reg20;iaf=reg21;
						
						fx=fx-ox*.05;fz=fz-oz*.05;
						reg18=fx;reg19=fz;
						
						ls=w/320;
						
						rd=rd*.9+.1;    rd=.1;     n=30; // Left wing 'Eye'
						rd=1;        k�    