module fc

type Expr =
    | Int of int
    | Add of Expr * Expr
    | Mul of Expr * Expr
    | Var of string

let glob = [ ("pi", 3); ("zero", 0) ]

let rec lookup (env: (string * int) list) (var: string) : int =
    match env with
    | [] -> failwith $"var: {var}"
    | (k, v) :: t -> if k = var then v else lookup t var

let rec eval (env: (string * int) list) (expr: Expr) : int =
    match expr with
    | Int n -> n
    | Add(x, y) -> eval env x + eval env y
    | Mul(x, y) -> eval env x * eval env y
    | Var v -> lookup env v

// System.NotImplementedException("You haven't

open NUnit.Framework

[<TestFixture>]
type TestClass() =

    let int123 = Int 123
    let add23 = Add(Int 2, Int 3)
    let mul45 = Mul(int123, add23)

    [<Test>]
    member this.``always ok``() = Assert.That(true, Is.True)

    [<Test>]
    member this.``int``() =
        Assert.That($"{int123}", Is.EqualTo "Int 123")

    [<Test>]
    member this.``add``() =
        Assert.That($"{add23}", Is.EqualTo "Add (Int 2, Int 3)")

    [<Test>]
    member this.``mul``() =
        Assert.That($"{mul45}", Is.EqualTo "Mul (Int 123, Add (Int 2, Int 3))")

    [<Test>]
    member this.``lookup pi``() =
        Assert.That(lookup glob "pi", Is.EqualTo 3)

    [<Test>]
    member this.``lookup zero``() =
        Assert.That(lookup glob "zero", Is.EqualTo 0)

    [<Test>]
    member this.``lookup undef``() =
        Assert.That(lookup glob "undef" , Throws.Exception)

[<EntryPoint>]
let main argv : int = 0
