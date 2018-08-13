
(cl:in-package :asdf)

(defsystem "pcd_object_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "SegmentedClusters" :depends-on ("_package_SegmentedClusters"))
    (:file "_package_SegmentedClusters" :depends-on ("_package"))
  ))