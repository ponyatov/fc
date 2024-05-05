module fc

let about = "F# compiler library"

type expr =
    | Int of int
    | Op of string * expr * expr

let i123 = Int 123
let add12 = Op("+", Int 1, Int 2)

let rec eval (e: expr) : int =
    match e with
    | Int i -> i
    | Op("+", e1, e2) -> eval e1 + eval e2
    | Op("*", e1, e2) -> eval e1 * eval e2
    | _ -> failwith ""

// eval Op("+", Int 1, Int 2)
