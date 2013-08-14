# learntris implementation in picolisp

(de handle (Ch)
   (case Ch
      ("q" (bye))))

(de mapstr (F Sym)
   (mapcar F (str Sym)) )

(de main ()
   (while (str (line))
      (mapstr handle @) ) )
