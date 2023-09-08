# Wmoge resource meta file
version: 1
uuid: 0
loader: default
class: PfxEffect
deps: [ "res://sprites/feather" ]
description: ""
params:
  type: Effect2d
  components:
    - amount: 20
      active: true
      features:
        - feature: Lifetime
          lifetime: 3.0
          infinite: false
        - feature: Movement2d
          speed_acceleration: "0 -5"
          angle_acceleration: 1.0
        - feature: Size
          start_size: 1
          end_size: 0
        - feature: Velocity2d
          radius: 1.0
        - feature: Color
          start_color: "1 1 1 0.6"
          end_color: "1 1 1 0"
        - feature: Sprite
          sprite: "res://sprites/feather"
          animation: 0