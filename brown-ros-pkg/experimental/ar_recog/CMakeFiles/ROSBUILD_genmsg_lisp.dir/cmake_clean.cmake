FILE(REMOVE_RECURSE
  "msg_gen"
  "srv_gen"
  "src/ar_recog/msg"
  "src/ar_recog/srv"
  "msg_gen"
  "srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "msg_gen/lisp/Tag.lisp"
  "msg_gen/lisp/_package.lisp"
  "msg_gen/lisp/_package_Tag.lisp"
  "msg_gen/lisp/Tags.lisp"
  "msg_gen/lisp/_package.lisp"
  "msg_gen/lisp/_package_Tags.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
