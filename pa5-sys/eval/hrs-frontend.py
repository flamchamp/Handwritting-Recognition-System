'''
==========================================================================
hrs-frontend.py
==========================================================================
A GUI frontend for handwritten recognition systems.

Author : Kaishuo Cheng, Yanghui Ou
  Date : Summer 2019

'''
import Tkinter as tk
import math
import os
import tkMessageBox
import sys
import os
from PIL import Image, ImageDraw, ImageFilter, ImageTk
import numpy as np
import subprocess

#-------------------------------------------------------------------------
# global variables
#-------------------------------------------------------------------------

yint = 0
root = tk.Tk()
root.configure(background='light grey')
root.resizable(0,0)
file_name  = 'image'
padding    = 8
traintime  = ''
infertime  = ''
label      = ''
method     = ''
dotsize    = 26
whiteratio = 20
canvasdege = 640

OPTIONS = [
  "LinearSearch",
  "BinarySearch",
  "TreeSearch",
  "TableSearch",
  "Alternative",
]

#-------------------------------------------------------------------------
# expand
#-------------------------------------------------------------------------

def expand( list, a, b ):

  k = len(list)
  sqk = int(math.sqrt(k))

  nl = [0] *k *a*b
  hsize = a*sqk
  vsize = b*sqk

  for i in range(k):
    x = i/sqk
    y = i%sqk
    value = list[i]
    for j in range(a):
      for k in range(b):
        indx = hsize*(x*b+k) + a*y+j
        nl[indx] = value

  return nl

blanklist = []
for i in range( 28 ):
  blanklist.append( [255]*28 )

blanklist = np.reshape( blanklist,( 1, -1 ) )
bl = expand( blanklist, 6, 5 )
bl = np.reshape( bl, (140, 168) )
blankfile = Image.fromarray( bl.astype('uint8') )

blankimg = ImageTk.PhotoImage(blankfile)

#linux2
if sys.platform == "darwin":
  canvas = tk.Canvas( root, width=641, height=640, bg = "white",
                      highlightthickness=1, highlightbackground="black" )
  whiteratio = 23
else:
  canvas = tk.Canvas( root, width=636, height=636, bg = "white",
                      highlightthickness=1, highlightbackground="black" )

canvas.grid( row = 0, column = 4, rowspan = 10,columnspan = 10,
             padx = (15,15), pady = (16, 15) )

#-------------------------------------------------------------------------
# makeit28
#-------------------------------------------------------------------------

def makeit28( lst ):
    b = []
    for l in range(28):
      b.append([0]*28)

    # FIXME: the following assertions fail
    # assert len(lst)%28 == 0,"number of rows of pixels not multiple of 28"
    # assert len(lst[0])%28 == 0,"number of pixels in a row not multiple of 28"
    vratio = len(lst)/28
    hratio = len(lst[0])/28
    for i in range(28):
      for j in range(28):
        cur_sum = 0
        for m in range(hratio):
          for n in range(vratio):
            vindx = i*vratio + m
            hindx = j*hratio + n
            cur_sum += lst[vindx][hindx]
        b[i][j] = cur_sum/(hratio*vratio)

    return b

#-------------------------------------------------------------------------
# run_backend
#-------------------------------------------------------------------------
# Parse the png image and runs the backend.

def run_backend( png_file ):
    global method

    im = Image.open( png_file ).convert('L')
    x  = im
    y  = np.asarray( x.getdata(),dtype=np.float64).reshape((x.size[1],x.size[0]))
    y  = np.asarray(y,dtype=np.uint8) #if values still in range 0-255!

    width   = float( im.size[0] )
    height  = float( im.size[1] )
    newlist = makeit28( y )

    tva = np.reshape( newlist, ( 1, -1 ) )
    tva = tva[0]

    nl = expand( tva, 6, 5 )
    nl = np.reshape( nl, ( 140, 168 ) )
    tva = [ (255 - x) for x in tva ]

    try:
      os.remove( './image.txt' )
    except:
       pass

    with open( 'image.txt', 'w' ) as f:
      for i in range( len(tva) ):
        item = str( tva[i] )
        f.write( item + ' ' )
        if ( i % 28 ) == 27:
          f.write("\n")

    try:
        os.remove('./my_plot.png')
    except:
        pass

    file = Image.fromarray( nl.astype('uint8') )
    width, height = file.size
    img2 = ImageTk.PhotoImage(file)

    panel.configure( image=img2 )
    panel.image = img2
    panel.grid( row = 7, column = 0, columnspan = 2, rowspan = 2,
                padx = (15,1), pady = (8,8), sticky = 'e' )

    # check if backend binary exists in current director
    if not os.path.exists( 'hrs-backend' ):
      print( 'Cannot find the backend binary!' )
      return

    p = subprocess.Popen(
      "./hrs-backend image.txt " + method,
      shell=True,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE
    ).communicate()[0]

    print( p )

    cimage = output_to_img( p )
    cnl = expand(cimage,6,5)
    cnl = np.reshape(cnl,(140,168))

    width, height = file.size
    cimage = np.reshape(cimage,(28,28))
    file = Image.fromarray(cnl.astype('uint8'))
    img2 = ImageTk.PhotoImage(file)
    panel2.configure(image=img2)
    panel2.image = img2
    panel2.grid( row = 9, column = 0, columnspan = 2, rowspan = 2,
                 padx = (15,1), pady =(8,14), sticky = 'e' )

#-------------------------------------------------------------------------
# output_to_img
#-------------------------------------------------------------------------

def output_to_img( p ):
  global traintime
  global infertime
  global label
  cimage = []

  trainindx = p.find("Training Time: ") #15

  inferindx = p.find("Inferene Time: ")#15
  labelindx = p.find("Prediction Label: ") #18
  imgindx = p.find("Prediction Match: ")#18
  traintime = p[trainindx+15:inferindx-1]
  infertime = p[inferindx+15:labelindx-1]
  label = p[labelindx+18:imgindx-1]

  img = p[imgindx+19:]
  x = 0
  while x < (len(img)-1):
    if img[x] != " " and  img[x] != "\n":

      if img[x+1] == " " or img[x+1] == "\n":
        cimage.append(255 - int(img[x]))

      elif img[x+2] == " " or img[x+2] == "\n":
        k = 255- 10*int(img[x]) - int(img[x+1])
        cimage.append(k)
        x = x+1

      else:
        k = 255 - 100* int(img[x]) - 10*int(img[x+1])-int(img[x+2])
        cimage.append(k)
        x = x+2

    x = x+1

  return cimage

#-------------------------------------------------------------------------
# clickrun
#-------------------------------------------------------------------------

def clickrun():
    global method
    global traintime
    global infertime
    global canvas
    try:
        os.remove('./' + file_name + '.png')
    except:
        pass
    method = variable.get()
    # drawline(canvasdege,"white")
    canvas.postscript(file = file_name + '.eps')
    # use PIL to convert to PNG
    img = Image.open(file_name + '.eps')
    img.save(file_name + '.png', 'png')
    run_backend('./'+file_name +'.png')
    e1.delete(0,tk.END)

    if len(traintime) > 5:
		traintime = traintime[:5]


    e1.insert(0,traintime+'s')
    e2.delete(0,tk.END)
    if len(infertime) > 5:
		infertime = infertime[:5]

    e2.insert(0,infertime+'s')
    e3.delete(0,tk.END)
    e3.insert(0,label)

#-------------------------------------------------------------------------
# close
#-------------------------------------------------------------------------

def close():
  global blankimg
  panel.grid_forget()
  panel2.grid_forget()
  panel.configure(image=blankimg)
  panel.image = blankimg
  panel.grid(row = 7, column = 0,columnspan = 2,rowspan = 2, padx = (15,1), pady = (8,8),sticky = 'e')
  panel2.configure(image=blankimg)
  panel2.image = blankimg
  panel2.grid(row = 9, column = 0,columnspan = 2,rowspan = 2, padx = (15,1), pady =(8,14),sticky = 'e')
  canvas.delete("all")
    # drawline(canvasdege)

#-------------------------------------------------------------------------
# helpme
#-------------------------------------------------------------------------

def helpme():
  tkMessageBox.showinfo("help",
    "Drag mouse on the canvas to draw.\n\n"
    "Choose your algorithm, and click run.\n\n"
    "Click reset to clear canvas.\n\n"
    "This GUI is created by Kaishuo Cheng\n\n"
    "under the guidance of Prof.Batten."
    "\n\nSummer2019 at Cornell "
  )

algo = tk.Label(root,
                text='Algorithm:', bg = "light grey")
algo.grid(row = 1, column = 0, pady = (0,0), padx = (padding,0))
variable = tk.StringVar(root)
variable.set(OPTIONS[0]) # default value

w = tk.OptionMenu(root, variable, *OPTIONS)

w.grid(row = 1, column = 1, pady = (0,0), padx = 2,sticky='we')

run = tk.Button(root,
                text='Run', command = clickrun, bg = "gray",highlightbackground = "gray"
                )
run.grid(row = 2, column = 1, pady = yint,sticky='we', padx = 2)
train = tk.Label(root,
                text='Train:', bg = "light grey")
train.grid(row = 3, column = 0, pady = yint,sticky='we')
infer = tk.Label(root,
                text='Inference:', bg = "light grey")
infer.grid(row = 4, column = 0, pady = yint,sticky='we')
pred = tk.Label(root,
                text='Prediction:', bg = "light grey")
pred.grid(row = 5, column = 0, pady = yint,sticky='we')
reset= tk.Button(root,
                text='Reset', command = close, bg = "gray",highlightbackground = "gray"
                )
reset.grid(row = 6, column = 1, pady = yint,sticky='we', padx = 2)

help= tk.Button(root,
                text='Instructions', command = helpme, bg = "gray",highlightbackground = "gray"
                )
help.grid(row = 0, column = 1, pady = (8,yint),sticky='we', padx = 2)
e1 = tk.Entry(root, width = 10,borderwidth=1,relief = "solid")
e1.insert(0,"0s")
e1.grid(row = 3, column = 1, pady = yint, padx = 2,sticky = 'we')
e1.config(justify = tk.RIGHT)

e2 = tk.Entry(root, width = 10,borderwidth=1, relief = "solid")
e2.insert(0,"0s")
e2.config(justify = tk.RIGHT)
e2.grid(row = 4, column = 1, pady = yint, padx = 2, sticky = 'we')

e3 = tk.Entry(root, width = 10,borderwidth=1, relief = "solid")
e3.insert(0,"0")
e3.grid(row = 5, column = 1, pady = yint, padx = 2, sticky = 'we')
e3.config(justify = tk.RIGHT)

algo.config(anchor = 'e')

train.config(anchor = 'e')
infer.config(anchor = 'e')

pred.config(anchor = 'e')
panel = tk.Label(root,borderwidth=1, relief = "solid", text = "input",bg = "white")
panel2 = tk.Label(root,borderwidth=1, relief="solid",text = "closest match",bg ="white")

panel.config(font=("normal", 15),compound = tk.BOTTOM)
panel2.config(font=("normal", 15),compound = tk.BOTTOM)

panel.configure(image=blankimg)
panel.image = blankimg
panel.grid(row = 7, column = 0,columnspan = 2,rowspan = 2, padx = (15,1), pady = (8,8),sticky = 'e')

panel2.configure(image=blankimg)
panel2.image = blankimg
panel2.grid(row = 9, column = 0,columnspan = 2,rowspan = 2, padx = (15,1), pady =(8,14),sticky = 'e')

#-------------------------------------------------------------------------
# drawdot
#-------------------------------------------------------------------------

def drawdot(eventorigin):
  global x, y

  x = eventorigin.x
  y = eventorigin.y

  canvas.create_oval( x-dotsize, y-dotsize, x+dotsize, y+dotsize, fill='black' )

#-------------------------------------------------------------------------
# drawline
#-------------------------------------------------------------------------

def drawline( edge, fill="black" ):
  global canvas
  if fill == "black":
    canvas.create_line(whiteratio*4, whiteratio*4, edge-whiteratio*4, whiteratio*4)
    canvas.create_line(whiteratio*4, whiteratio*4, whiteratio*4, edge-whiteratio*4)
    canvas.create_line( edge-whiteratio*4, whiteratio*4, edge-whiteratio*4, edge-whiteratio*4)
    canvas.create_line(whiteratio*4,  edge-whiteratio*4, edge-whiteratio*4, edge-whiteratio*4)
  else:
    canvas.create_line(whiteratio*4, whiteratio*4, edge-whiteratio*4, whiteratio*4,fill = fill)
    canvas.create_line(whiteratio*4, whiteratio*4, whiteratio*4, edge-whiteratio*4,fill = fill)
    canvas.create_line( edge-whiteratio*4, whiteratio*4, edge-whiteratio*4, edge-whiteratio*4,fill = fill)
    canvas.create_line(whiteratio*4,  edge-whiteratio*4, edge-whiteratio*4, edge-whiteratio*4,fill = fill)
  return

canvas.bind("<Button 1>",drawdot)
canvas.bind("<B1-Motion>",drawdot)

#=========================================================================
# main
#=========================================================================

if __name__ == '__main__':
  root.mainloop()
