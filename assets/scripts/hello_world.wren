import "core/wren_behaviour" for WrenBehaviour

class HelloWord is WrenBehaviour {
    construct new() {
        super()
    }

    update() {
        System.print("Hello, world!")
    }
}
