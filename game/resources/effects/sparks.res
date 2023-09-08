# Wmoge resource meta file
version: 1
uuid: 0
loader: default
class: PfxEffect
deps: [ "res://sprites/spark" ]
description: ""
params:
  type: Effect2d
  components:
    - amount: 40
      active: true
      features:
        - feature: Lifetime
          lifetime: 2.0
          infinite: false
        - feature: Movement2d
          speed_acceleration: "0 -40"
          angle_acceleration: 2.0
        - feature: Size
          start_size: 1
          end_size: 0
        - feature: Velocity2d
          radius: 15.0
        - feature: Color
          start_color: "1 1 1 0.8"
          end_color: "1 1 1 0"
        - feature: Sprite
          sprite: "res://sprites/spark"
          animation: 0