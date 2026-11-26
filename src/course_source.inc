#include "topics.h"
#include "maths_details.inc"

#define N(detail,t,n,m,e) {t,n,m,e,Calculate,0,{0},{0},&detail}
#define C(detail,t,n,m,o,l,v) {t,n,m,0,o,0,{l},{v},&detail}
#define D(detail,t,n,m,v,a,b) {t,n,m,0,Definite,0,{"Integrand f(x)","Lower limit","Upper limit"},{v,a,b},&detail}
#define F1(detail,t,n,m,f,l1,v1) {t,n,m,0,Calculate,f,{l1},{v1},&detail}
#define F2(detail,t,n,m,f,l1,v1,l2,v2) {t,n,m,0,Calculate,f,{l1,l2},{v1,v2},&detail}
#define F3(detail,t,n,m,f,l1,v1,l2,v2,l3,v3) {t,n,m,0,Calculate,f,{l1,l2,l3},{v1,v2,v3},&detail}
#define F4(detail,t,n,m,f,l1,v1,l2,v2,l3,v3,l4,v4) {t,n,m,0,Calculate,f,{l1,l2,l3,l4},{v1,v2,v3,v4},&detail}
#define COUNT(a) ((int)(sizeof(a)/sizeof(*(a))))
#define CH(t,a) {t,a,COUNT(a)}

static const Topic ig_number[] = {
    F2(ig_number_1, "Integers, primes and HCF","Prime factors build every integer greater than one. The HCF uses common prime factors.","Find the largest positive integer dividing both numbers. For the LCM, divide the product by the HCF.","gcd($1,$2)","First integer","84","Second integer","126"),
    C(ig_number_2, "Fractions and decimals","A fraction means numerator divided by denominator. Recurring decimals can be converted by subtracting a shifted copy.","Find a common denominator before adding or subtracting. To divide, multiply by the reciprocal.",Calculate,"Fraction calculation","2/3+3/8"),
    C(ig_number_3, "Powers, roots and surds","For the same base, add powers in a product and multiply powers for a power of a power. Negative powers give reciprocals.","Write a radicand as a product containing the largest square factor. For an irrational denominator use a suitable conjugate.",Calculate,"Numeric calculation","sqrt(72)/sqrt(2)"),
    N(ig_number_4, "Sets and Venn diagrams","Union includes either set. Intersection includes both. A complement consists of elements outside the set.","Fill the intersection first, then each exclusive region, then the outside. Use total = union + neither.","In a class of 30, 18 take music, 14 take art and 7 take both.\nUnion = 18 + 14 - 7 = 25.\nNeither = 30 - 25 = 5."),
    F3(ig_number_5, "Percentages and interest","A rise of r% has multiplier 1+r/100. A fall uses 1-r/100. Divide by the multiplier for a reverse percentage.","Raise the multiplier to the number of periods and multiply by the initial amount.","$1*(1+$2/100)^$3","Initial amount","250","Growth per period (%)","4","Periods","3"),
    F3(ig_number_6, "Ratio and proportion","Ratios compare quantities in the same units. A share is total times its fraction of the parts.","Add the ratio parts. Multiply the total by the first part divided by their sum.","$1*$2/($2+$3)","Total to share","84","First ratio part","2","Second ratio part","5"),
    N(ig_number_7, "Rounding and bounds","A value rounded to the nearest unit u represents an interval starting half a unit below it.","For positive a/b the upper bound uses the upper bound of a and lower bound of b.","7.4 cm to the nearest 0.1 cm.\nHalf a step is 0.05 cm.\n7.35 <= length < 7.45 cm."),
    C(ig_number_8, "Standard form","Write a number as a*10^n with 1 <= a < 10 and integer n.","Multiply or divide the coefficients and combine powers of ten. Adjust the final coefficient and exponent together.",Calculate,"Standard-form calculation","(3*10^5)*(2*10^-3)"),
    C(ig_number_9, "Rates and calculator skills","Use consistent units when calculating speed, density, money conversion and other rates.","Identify the units and write the conversion within the calculation. Use brackets around a complete numerator or denominator.",Calculate,"Numeric calculation","150/(2+30/60)")
};

static const Topic ig_algebra[] = {
    C(ig_algebra_1, "Expressions and identities","An identity is true for all permitted inputs. A formula relates named quantities.","Use distribution to remove brackets and collect like terms. Rearrange a formula by applying inverse operations to both sides.",Expand,"Expression in x","(x+4)(x-3)"),
    C(ig_algebra_2, "Linear equations","A linear equation in x has degree one after simplification.","Gather the x terms on one side, the constants on the other, then divide by the coefficient of x.",Solve,"Equation in x","5x-7=3x+9"),
    C(ig_algebra_3, "Quadratic equations","A quadratic has the form ax^2+bx+c with a non-zero. A zero product gives roots from each factor.","Set the expression to zero. Factorise where possible or use the quadratic formula.",Solve,"Equation in x","2x^2-7x+3=0"),
    F4(ig_algebra_4, "Direct and inverse proportion","Direct proportion has the form y=k*x^n. Inverse proportion uses a negative power.","Divide the known y by its x raised to the given power to find k. Substitute the new x.","($2/$1^$3)*$4^$3","Known x","2","Known y","12","Power n","2","New x","5"),
    N(ig_algebra_5, "Simultaneous equations","An ordered pair must satisfy both equations. Use elimination or substitution.","Make one pair of coefficients equal, then add or subtract to remove that unknown.","Solve 2x+y=8, x-y=1.\nAdd: 3x=9, so x=3.\nThen y=2. Check: 6+2=8."),
    N(ig_algebra_6, "Inequalities","An inequality describes a range of solutions. A strict boundary is excluded.","Reverse the direction when multiplying or dividing by a negative. Use a sign chart for quadratic inequalities.","Solve -3x+2 > 11.\nSubtract 2: -3x > 9.\nDivide by -3 and reverse: x < -3.")
};

static const Topic ig_graphs[] = {
    F3(ig_graphs_1, "Sequences and nth term","An arithmetic sequence has constant first difference d. Constant second differences indicate a quadratic sequence.","Use term n = a + (n-1)d. For a quadratic sequence, halve the second difference for the coefficient of n^2.","$1+($3-1)*$2","First term a","5","Difference d","3","Term number n","12"),
    N(ig_graphs_2, "Functions and inverses","f(x) names a function value. A composite applies the inner function first.","For an inverse, write y=f(x), rearrange for x, swap x and y and check the domain.","f(x)=3x-2, g(x)=x^2.\nf(g(4))=3(16)-2=46.\nIf y=3x-2 then x=(y+2)/3.\nThe inverse maps x to (x+2)/3."),
    {"Graphs and coordinates","A gradient is change in y over change in x. The gradient of a distance-time graph is speed.","Make a table of values, locate intercepts, and use the scale. A graph intersection solves both equations.",0,Substitute,0,{"Function y=f(x)","Value of x"},{"x^2-4x+3","2"},&ig_graphs_3},
    C(ig_graphs_4, "Differentiation and turning points","The derivative gives gradient. Stationary points occur where f'(x)=0.","Apply the power rule. Solve f'(x)=0 and check the sign change on either side.",Differentiate,"Polynomial f(x)","x^3-6x^2+9x")
};

static const Topic ig_geometry[] = {
    N(ig_geometry_1, "Angles and parallel lines","Straight-line angles sum to 180 degrees. Angles around a point sum to 360. Vertically opposite angles are equal.","On parallel lines use equal alternate or corresponding angles, and supplementary co-interior angles.","Co-interior angles are x and 118 degrees.\nx+118=180, so x=62 degrees."),
    F1(ig_geometry_2, "Polygons and symmetry","For a regular n-gon each exterior angle is 360/n. Interior and exterior angles at a vertex add to 180.","Triangulate an n-gon from one vertex to see (n-2) triangles. Divide the total by n for one regular interior angle.","($1-2)*180/$1","Number of sides","9"),
    N(ig_geometry_3, "Measures and constructions","Use metric conversions, scales and bearings. A bearing is measured clockwise from north to three figures.","Use equal-radius arcs for perpendicular bisectors. Use the angle bisector for points equidistant from intersecting lines.","With map scale 1:25000 and map distance 6 cm:\nActual distance = 150000 cm = 1.5 km."),
    N(ig_geometry_4, "Circle theorems","A diameter subtends a right angle at the circumference. Opposite angles in a cyclic quadrilateral sum to 180.","Name each theorem used. Radius meets tangent at 90 degrees. The tangent-chord angle equals the angle in the alternate segment.","An arc subtends a 104 degree angle at the centre. The same arc gives 104/2 = 52 degrees at the circumference."),
    N(ig_geometry_5, "Geometrical reasoning","Congruency tests include SSS, SAS, ASA and RHS. Similar shapes have equal corresponding angles.","Match corresponding vertices. Give a theorem or listed condition for each equality in your proof.","Triangles with side lengths 3,4,5 and 5,3,4 are congruent by SSS."),
    F2(ig_geometry_6, "Pythagoras and right triangles","For a right triangle a^2+b^2=c^2, with c the hypotenuse. Use SOH CAH TOA for angles.","Square both perpendicular sides, add and take the positive square root.","sqrt($1^2+$2^2)","First leg","6","Second leg","8"),
    F3(ig_geometry_7, "Sine and cosine rules","Use a/sin A=b/sin B for opposite pairs. The cosine rule uses two sides and their included angle.","Calculate c with c^2=a^2+b^2-2ab cos C. Angle C is entered in degrees.","sqrt($1^2+$2^2-2*$1*$2*cos($3))","Side a","7","Side b","9","Angle C (degrees)","60"),
    F2(ig_geometry_8, "Area, arcs and sectors","Arc length = angle/360 times circumference. Sector area = angle/360 times circle area.","Use the fraction of a full turn and multiply by pi*r^2 for the sector area.","pi*$1^2*$2/360","Radius","8","Sector angle (degrees)","45"),
    F2(ig_geometry_9, "Surface area and volume","A prism has uniform cross-section. A cone or pyramid has a third of the corresponding prism volume.","Multiply base area by perpendicular height, then divide by three for a pyramid.","$1*$2/3","Pyramid base area","36","Perpendicular height","10"),
    F3(ig_geometry_10, "Similarity and scale factors","Length changes by k, area by k^2 and volume by k^3.","Choose dimension 1 for length, 2 for area, or 3 for volume. Apply the corresponding power of k.","$1*$2^$3","Original measure","12","Length scale factor","1.5","Dimension (1, 2 or 3)","2")
};

static const Topic ig_vectors[] = {
    F2(ig_vectors_1, "Vectors","Vectors have magnitude and direction. AB = OB - OA. Parallel vectors are scalar multiples.","Add and subtract corresponding components. Use Pythagoras to find magnitude.","sqrt($1^2+$2^2)","x component","5","y component","-12"),
    N(ig_vectors_2, "Transformations","Specify mirror line, rotation centre and angle, translation vector, or enlargement centre and scale factor.","For an enlargement find the displacement from the centre, scale it, then add it back to the centre.","Enlarge P=(4,1) about C=(2,2) by scale -2.\nCP=(2,-1); scaled=(-4,2).\nImage = (-2,4).")
};

static const Topic ig_stats[] = {
    N(ig_stats_1, "Charts and data representation","Bar charts compare categories. Histograms represent continuous grouped data. Cumulative frequency tracks running totals.","For a histogram use frequency density = frequency/class width. Read median and quartiles from cumulative frequency.","12 values lie in 10 <= x < 15.\nWidth = 5, so frequency density = 12/5 = 2.4."),
    F4(ig_stats_2, "Averages and spread","Mean = total/count. Median is the middle ordered value. Range is largest minus smallest.","For grouped data use class midpoints. For a frequency table multiply each value by its frequency.","($1*$2+$3*$4)/($2+$4)","First value","10","First frequency","3","Second value","16","Second frequency","5"),
    F2(ig_stats_3, "Probability and tree diagrams","Probabilities sum to one across exhaustive outcomes. Independent events do not change one another's probabilities.","Multiply along a tree path and add mutually exclusive paths. For sampling without replacement update the second probability.","$1*$2","First branch probability","3/5","Next branch probability","2/4")
};

static const Topic ocr_algebra[] = {
    C(ocr_algebra_1, "Polynomial algebra","Use the factor theorem: x-r divides f(x) when f(r)=0. A division remainder equals f(r).","Expand and collect coefficients. For division, cancel the leading power repeatedly.",Factorise,"Polynomial in x","2x^3-3x^2-8x+12"),
    N(ocr_algebra_2, "Algebraic fractions and surds","Use a common denominator. Factor and retain original restrictions when cancelling. Rationalise with a conjugate.","Factor each radicand to extract squares. Multiply both parts of a fraction by a suitable radical or conjugate.","2/(x-1)-1/(x+1) = (x+3)/(x^2-1), x != +/-1.\nsqrt(12)+sqrt(27)=5*sqrt(3)."),
    N(ocr_algebra_3, "Completing the square","Write ax^2+bx+c as a(x+b/(2a))^2+c-b^2/(4a).","Factor out a from x terms. Halve the linear coefficient inside the bracket, square it, then adjust the constant.","2x^2+12x+11 = 2(x+3)^2-7.\nThe minimum is -7 at x=-3."),
    C(ocr_algebra_4, "Linear, quadratic and cubic equations","Translate the context into equations. For two unknowns, eliminate one using substitution or addition.","Collect all terms on one side. For a cubic, find a linear factor and solve the remaining quadratic.",Solve,"Equation in x","x^3-6x^2+11x-6=0"),
    N(ocr_algebra_5, "Inequalities and regions","For quadratic inequalities divide the number line at the roots. A linear inequality in x and y picks one half-plane.","Plot a boundary, use dashed for strict or solid for inclusive, and test a point on one side.","x^2-5x+6 <= 0 factors as (x-2)(x-3) <= 0. It is non-positive on 2 <= x <= 3."),
    N(ocr_algebra_6, "Recurrence relationships","A recurrence describes each term from earlier terms and needs initial data.","Substitute the current value into the rule for each new term. In a model, interpret parameters and limitations.","u(0)=10, u(n+1)=0.8u(n)+4.\nu(1)=12, u(2)=13.6.\nA fixed point L satisfies L=0.8L+4, so L=20.")
};

static const Topic ocr_counting[] = {
    C(ocr_counting_1, "Binomial expansion","Binomial coefficients count selections of positions for the second term.","Expand in ascending powers by multiplying each coefficient by the matching powers of both terms.",Expand,"Binomial expression","(2+3x)^5"),
    N(ocr_counting_2, "Counting and representations","For successive choices, multiply the number of options at each stage. Trees, Venn diagrams and two-way tables can organise outcomes.","Check that your categories are exhaustive and avoid counting overlapping cases twice.","Three shirt choices and four trouser choices give 3*4=12 outfits. A two-way table gives one cell per outfit."),
    F2(ocr_counting_3, "Permutations and combinations","Order matters for nPr; order is irrelevant for nCr. nCr=nPr/r!.","Multiply descending factors for ordered selections. Divide by r! for unordered selections.","ncr($1,$2)","Items n","10","Chosen r","3"),
    F3(ocr_counting_4, "Binomial probabilities","In (a+b)^n the coefficient in term r is nCr. For a count X from independent Bernoulli trials, X is binomial.","For P(X=r), multiply nCr by p^r and (1-p)^(n-r).","binom($1,$2,$3)","Trials n","5","Successes r","2","Probability p","1/3")
};

static const Topic ocr_coords[] = {
    F4(ocr_coords_1, "Lines and gradients","Parallel gradients are equal. Non-vertical perpendicular gradients multiply to -1.","Compute gradient (y2-y1)/(x2-x1), then use y-y1=m(x-x1).","($4-$2)/($3-$1)","x1","1","y1","4","x2","5","y2","12"),
    N(ocr_coords_2, "Circles and intersections","A circle is (x-a)^2+(y-b)^2=r^2. A radius and tangent are perpendicular at the point of contact.","Complete both squares to retrieve the centre. Substitute a line into the circle equation to find intersections.","x^2+y^2-4x+6y=12 gives (x-2)^2+(y+3)^2=25.\nCentre (2,-3), radius 5."),
    N(ocr_coords_3, "Sketching and reading graphs","Identify intercepts, asymptotes, turning points and symmetry. A tangent or normal gives local gradient information.","For a polynomial, start with factorised roots and the leading term. Use the derivative to locate stationary points.","y=x(x-2) crosses at 0 and 2. Its gradient 2x-2 vanishes at x=1, where y=-1."),
    N(ocr_coords_4, "Linear programming","Each linear inequality bounds a half-plane. The feasible region meets every constraint.","Find the vertices of the feasible region and evaluate the linear objective at each vertex.","Maximise 3x+2y given x+y<=4, x<=3, x,y>=0.\nVertices (0,0),(3,0),(3,1),(0,4) give 0,9,11,8.\nMaximum is 11 at (3,1).")
};

static const Topic ocr_trig[] = {
    F3(ocr_trig_1, "Pythagoras in 3D","Extend Pythagoras with a horizontal diagonal followed by a vertical right triangle.","Add three squared perpendicular components and take the square root.","sqrt($1^2+$2^2+$3^2)","Length","3","Width","4","Height","12"),
    F3(ocr_trig_2, "Non-right triangles","Use the cosine rule for included angle data and the sine rule for opposite pairs. Triangle area is ab*sin(C)/2.","Enter the lengths around angle C and C in degrees.","$1*$2*sin($3)/2","Side a","10","Side b","8","Included angle (degrees)","30"),
    N(ocr_trig_3, "Trig graphs and identities","sin^2(x)+cos^2(x)=1 and tan(x)=sin(x)/cos(x) where defined.","Use a principal angle, symmetry and periodicity. List every solution within the stated interval.","Solve sin x=1/2 for 0 <= x < 360 degrees.\nPrincipal angle 30. Its reflection is 150.\nSolutions: 30, 150 degrees.")
};

static const Topic ocr_calc[] = {
    C(ocr_calc_1, "Gradients and differentiation","Use dy/dx for a curve's gradient. Tangents have that gradient at the contact point.","Multiply each power term by its exponent and decrease the exponent by one.",Differentiate,"Polynomial f(x)","3x^4-8x^2+2"),
    N(ocr_calc_2, "Tangents and normals","The derivative at x=a gives the tangent gradient. The normal is perpendicular to the tangent.","Find f(a) and f'(a). Use y-y1=m(x-x1) for each line. If f'(a)=0, the normal is x=a.","For f=x^2 at x=2, the point is (2,4) and f'=4.\nTangent y-4=4(x-2).\nNormal y-4=-(x-2)/4."),
    N(ocr_calc_3, "Stationary points and optimisation","A local minimum has derivative changing from negative to positive. At a maximum the change is reversed.","Model the quantity to optimise. Find stationary points, classify them and consider allowed endpoints.","A(x)=x(10-x).\nA'=10-2x=0 at x=5, and A''=-2.\nMaximum A=25 for 0 <= x <= 10."),
    D(ocr_calc_4, "Integration and area","An antiderivative reverses differentiation. A definite integral gives signed area.","Increase each power by one and divide by the new power. Evaluate at the upper limit minus the lower.","3x^2+2x","0","2"),
    N(ocr_calc_5, "Calculus in kinematics","Velocity is the derivative of displacement. Acceleration is the derivative of velocity.","Integrate to recover displacement or velocity. Use initial conditions to determine constants.","s=2t^3-3t^2.\nv=6t^2-6t, a=12t-6.\nAt t=2, v=12 and a=18.")
};

static const Topic ocr_numerical[] = {
    N(ocr_numerical_1, "Sign changes and iteration","A continuous function changing sign has a root in the interval. Repeated iteration can approach a fixed point.","Evaluate each endpoint, then bisect or refine. Check for convergence if iterating x(n+1)=g(x(n)).","f(x)=x^3+x-4.\nf(1)=-2, f(2)=6, so a root lies between 1 and 2.\nf(1.5)=0.875, so refine to (1,1.5)."),
    F4(ocr_numerical_2, "Chord estimate of a gradient","The secant gradient approximates a tangent gradient when the two sampled points are close to the point of interest.","Calculate change in y over change in x. Move the points closer to improve the estimate for a smooth curve.","($4-$2)/($3-$1)","Left x","1.9","Left y","3.61","Right x","2.1","Right y","4.41"),
    F4(ocr_numerical_3, "Trapezium rule","Approximate area with equally spaced ordinates. Interior ordinates are counted twice. Rectangular strips use one height each.","For two strips, multiply half the step width by y0+2y1+y2.","$1*($2+2*$3+$4)/2","Strip width h","1","First ordinate","1","Middle ordinate","2","Last ordinate","5")
};

static const Topic ocr_exponent[] = {
    F3(ocr_exponent_1, "Exponential growth and decay","Exponential models use a constant multiplier in each equal time period.","Multiply the initial value by the multiplier raised to the number of periods.","$1*$2^$3","Initial value","120","Multiplier per period","0.9","Periods","7"),
    N(ocr_exponent_2, "Log graphs and model fitting","For y=ka^x, plot log y against x. For y=kx^n, plot log y against log x.","The intercept gives log k. The gradient is log a or n, depending on the model.","If log10 y = 1+2 log10 x, then k=10 and n=2. So y=10x^2."),
    F2(ocr_exponent_3, "Logarithms and equations","log_b(a) is the exponent on b giving a. Products become sums in logs and powers become multipliers.","For b^x=a, take logs on both sides and divide by ln b.","ln($1)/ln($2)","Target a","45","Base b","3")
};

static const Topic al_proof[] = {
    N(al_proof_1, "Proof and counterexamples","Use deduction, exhaustion, contradiction and counterexample where appropriate.","State assumptions and justify each step. To disprove a universal claim, supply one valid exception.","Prove that the square of every odd integer is odd.\nLet n=2k+1. Then n^2=2(2k^2+2k)+1, which is odd.")
};

static const Topic al_algebra[] = {
    C(al_algebra_1, "Indices, surds and polynomials","Use rational powers for roots and simplify surds exactly. The factor theorem tests linear factors.","Collect like powers, use long division where necessary, and keep the domain when manipulating expressions.",Factorise,"Polynomial in x","x^3-x^2-4x+4"),
    C(al_algebra_2, "Quadratics and equations","The discriminant b^2-4ac classifies roots. Completing the square gives the turning point.","For a disguised quadratic, substitute for a repeated term, solve, then back-substitute and check the domain.",Solve,"Equation in x","x^2-4x+1=0"),
    N(al_algebra_3, "Inequalities and modulus","Absolute value measures distance from zero. Quadratic and rational inequalities require sign analysis.","Split at zeros of factors and at excluded points. Use a sign chart before choosing intervals.","|2x-3|<5 means -5<2x-3<5.\nAdd 3 and divide by 2: -1<x<4."),
    N(al_algebra_4, "Functions and transformations","Know composite, inverse and modulus functions and domain and range. f(x+a) shifts left by a; f(x)+a shifts up.","Transform inside changes on the x-axis and outside changes on the y-axis. Reflect across y=x for the inverse.","For f(x)=x^2, 2f(x-3)+1 has vertex (3,1) and vertical stretch factor 2."),
    N(al_algebra_5, "Partial fractions","Decompose rational functions with distinct or repeated linear factors. Divide first if the fraction is improper.","Multiply through by the denominator. Substitute roots or equate coefficients to recover the constants.","(3x+5)/((x+1)(x+2)) = 2/(x+1)+1/(x+2).\nCheck: 2(x+2)+(x+1)=3x+5.")
};

static const Topic al_coord[] = {
    F4(al_coord_1, "Lines and coordinate geometry","Find equation, midpoint, distance or gradient using two points. For perpendicular lines use the negative reciprocal gradient.","Subtract corresponding coordinates. Square, add and take a square root to find length.","sqrt(($3-$1)^2+($4-$2)^2)","x1","-3","y1","1","x2","1","y2","4"),
    N(al_coord_2, "Circles and tangents","Use the centre-radius form, perpendicular radii and chord symmetry.","Find the radius gradient to the contact point, then the tangent gradient. Use the point-gradient line.","Circle centre (1,2), contact (4,6).\nRadius gradient 4/3, tangent gradient -3/4.\ny-6=(-3/4)(x-4)."),
    N(al_coord_3, "Parametric equations","A parameter describes x and y together, often with a specified domain.","Eliminate the parameter only where valid. Track direction and restrictions when identifying the curve.","x=2t+1, y=t^2, t>=0.\nt=(x-1)/2.\ny=(x-1)^2/4 for x>=1.")
};

static const Topic al_series[] = {
    F3(al_series_1, "Arithmetic sequences and sums","Term n is a+(n-1)d. The sum is n/2 times the first plus last term.","Find the last term from the common difference, then multiply the mean of the endpoints by n.","$3*(2*$1+($3-1)*$2)/2","First term a","4","Difference d","3","Terms n","12"),
    F3(al_series_2, "Geometric sequences and sums","Term n is ar^(n-1). An infinite sum exists for |r|<1 and equals a/(1-r).","Use a(1-r^n)/(1-r) for a finite sum, or na when r=1.","$1*(1-$2^$3)/(1-$2)","First term a","12","Ratio r (r != 1)","0.5","Terms n","5"),
    N(al_series_3, "Binomial expansions","For integer n>=0 the expansion is finite. For a general index, the series for (1+x)^n needs |x|<1.","Use coefficient n(n-1)...(n-r+1)/r! for the x^r term. Factor out any constant first.","(1+2x)^(-1)=1-2x+4x^2-8x^3+... for |x|<1/2.")
};

static const Topic al_trig[] = {
    F2(al_trig_1, "Radians, arcs and sectors","An angle in radians equals arc length divided by radius. Sector area is r^2*theta/2.","Convert degrees by multiplying by pi/180. Substitute radians into the formula.","$1^2*$2/2","Radius","5","Angle (radians)","pi/3"),
    N(al_trig_2, "Trig functions and equations","Know reciprocal functions, inverse functions, graphs, identities and exact values. Respect each function's domain.","Find the principal value, use periodicity and reflect as appropriate. Check the required interval.","For 0 <= x < 2pi, cos x=-1/2 gives x=2pi/3 or 4pi/3."),
    N(al_trig_3, "Compound and double angles","Use sin(A+B)=sin A cos B + cos A sin B. With A=B recover double-angle formulae.","To write a sin x+b cos x as R sin(x+d), match R cos d=a and R sin d=b.","Write 3sin x+4cos x as 5sin(x+d), where d=atan(4/3).\nThe maximum is 5."),
    N(al_trig_4, "Trig modelling and triangles","Use sinusoidal models with amplitude, period, phase and vertical shift. Use triangle rules to describe geometric contexts.","Read the midline from half the sum of extremes. The amplitude is half their difference.","Highest 11, lowest 3, period 12. A cosine model peaking at t=0 is 7+4cos(pi*t/6).")
};

static const Topic al_logs[] = {
    F3(al_logs_1, "Exponentials and logarithms","y=Ae^(kt) models continuous growth or decay. The natural logarithm inverts exp.","For y=Ae^(kt), rearrange to ln(y/A)=kt, then divide by k.","ln($2/$1)/$3","Initial A","100","Target y","200","Growth constant k","0.05"),
    N(al_logs_2, "Log models and straight lines","Taking logs gives ln y=ln A+kx for y=Ae^(kx), and ln y=ln A+n ln x for y=Ax^n.","Choose the axes to straighten the model. Interpret intercept as ln A and gradient according to the model.","If ln y=2+3 ln x, exponentiate to obtain y=e^2*x^3.")
};

static const Topic al_diff[] = {
    C(al_diff_1, "Power, product and chain rules","Differentiate powers, exponential, logarithm and trig functions. Use radians for standard trig derivatives.","Use the product, quotient or chain rule according to the outermost operation. Simplify the resulting expression.",Differentiate,"Function f(x)","x^2*exp(-x)"),
    N(al_diff_2, "Implicit and parametric calculus","Implicitly differentiate both sides; a y term uses the chain rule. Parametrically dy/dx=(dy/dt)/(dx/dt).","Differentiate, collect dy/dx terms and isolate it. Substitution gives the gradient at a specified point.","x^2+y^2=25 gives 2x+2y*y'=0, so y'=-x/y where y != 0."),
    N(al_diff_3, "Stationary points and concavity","The second derivative describes concavity. Stationary points have f'=0; inflections change concavity.","Find the stationary points and classify them with a sign change of f' or the second derivative.","f=x^3-3x. f'=3x^2-3.\nf'=0 at x=-1 and 1. f''=6x.\nLocal max at -1, local min at 1."),
    N(al_diff_4, "Rates of change and optimisation","A related-rate problem differentiates quantities with respect to time.","Write the relationship, differentiate using the chain rule and substitute numerical values last.","A=pi*r^2 gives dA/dt=2pi*r*dr/dt. At r=5, dr/dt=2, the rate is 20pi.")
};

static const Topic al_integral[] = {
    C(al_integral_1, "Antiderivatives and substitution","An antiderivative F satisfies F'=f. A substitution can turn a composed function into a standard integral.","Recognise the derivative of the inner function and account for its constant factor. Include +C.",Integrate,"Integrand f(x) (radians)","3exp(2x+1)-2sin(3x)"),
    D(al_integral_2, "Definite integrals and area","Integrals below the x-axis contribute negative signed area. Find intersections for area between two curves.","Integrate upper minus lower on each subinterval where their order is constant.","4-x^2","-2","2"),
    N(al_integral_3, "Integration by parts","The product rule yields integral u dv = uv - integral v du.","Choose u so it becomes simpler after differentiation. Integrate dv to obtain v.","Integral x exp(x) dx.\nChoose u=x, v=exp(x).\nResult: x exp(x)-exp(x)+C."),
    N(al_integral_4, "Partial fractions in integration","Decompose a rational integrand first to obtain standard logarithmic or power integrals.","For 1/(ax+b), use (1/a)ln|ax+b| wherever ax+b is non-zero.","Integral 2/(x+1)+1/(x+2) dx = 2ln|x+1|+ln|x+2|+C."),
    N(al_integral_5, "Differential equations","Separate variables where possible and integrate both sides. Use initial conditions to identify the particular solution.","For dy/dx=k*y, separate dy/y=k dx, integrate, then solve for y. Include equilibrium where appropriate.","dy/dx=2y, y(0)=3.\nln|y|=2x+C, hence y=3e^(2x)."),
    N(al_integral_6, "Parametric area","When x=x(t), dx=x'(t)dt. Use the correct orientation and limits.","Integrate y(t)x'(t) between the parameter endpoints. Split if needed when direction or sign changes.","x=t^2, y=t, 0<=t<=2.\nArea = integral 2t^2 dt from 0 to 2 = 16/3.")
};

static const Topic al_numerical[] = {
    N(al_numerical_1, "Location of roots and iteration","A sign change of a continuous function brackets at least one root. Fixed-point iteration uses x(n+1)=g(x(n)).","Keep track of the bracket. When iterating, compare consecutive estimates and check the original equation.","For cos x=x with radians, x0=1 gives x1=0.5403, x2=0.8576. Iteration approaches about 0.7391."),
    F3(al_numerical_2, "Newton-Raphson","Newton-Raphson uses the tangent intercept and may fail near zero derivative or for a poor starting point.","Use x_new=x-f(x)/f'(x). Repeat with updated values if needed.","$1-$2/$3","Current x","2","f(x)","1","f'(x)","4"),
    F4(al_numerical_3, "Trapezium rule","With step h, approximate the integral as h/2 times first + last + twice all interior heights.","Enter the step and the three heights for two strips. Compare the curve and chords for bias.","$1*($2+2*$3+$4)/2","Step h","1","y0","1","y1","2","y2","5")
};

static const Topic al_vectors[] = {
    F3(al_vectors_1, "Vectors in 2D and 3D","Use components, magnitude and position vectors. Parallel vectors are scalar multiples.","Find AB by subtracting the position vector of A from B. Then use the square root of the sum of squares.","sqrt($1^2+$2^2+$3^2)","x component","2","y component","3","z component","6"),
    N(al_vectors_2, "Vector geometry","Translate geometry into vector equations and use components to prove lengths and parallelism.","Equate components when finding unknown scalars. Equal magnitudes alone do not prove vectors equal.","AB=(2,4,-2) and CD=(-1,-2,1).\nAB=-2CD, so the segments are parallel.")
};

static const Topic al_sampling[] = {
    N(al_sampling_1, "Sampling methods","Study random, systematic, stratified, quota and opportunity sampling and their limitations.","Identify population, frame and sample. In proportional stratification allocate by each group's population share.","A stratum of size 45 in a population of 180 takes 45/180 of a sample of 40, so select 10."),
    N(al_sampling_2, "Large data set","Interpret data in context, including weather units, missing values, trace values, and sampling bias.","Check the variable definition and units before comparing observations across places or dates.","Record wind direction as categorical where given as compass points. A numerical mean of codes would be misleading.")
};

static const Topic al_data[] = {
    N(al_data_1, "Data presentation and outliers","Use histograms, box plots, scatter plots, cumulative frequency and measures of location and spread.","Compare centre and spread in context. Apply a specified outlier rule and interpret association separately from causation.","Q1=12, Q3=20, IQR=8.\nUsing 1.5*IQR, bounds are 0 and 32, so 35 is an outlier."),
    F2(al_data_2, "Variance and coding","For a population, variance is mean(x^2)-mean(x)^2. Standard deviation is its square root.","For y=(x-a)/b, reverse the coding using mean(x)=a+b*mean(y). SD scales by |b|.","sqrt($1-$2^2)","Mean of squares","34","Mean","5")
};

static const Topic al_probability[] = {
    F2(al_probability_1, "Conditional probability","P(A|B)=P(A intersect B)/P(B). Independence gives P(A|B)=P(A) when P(B)>0.","Divide the probability of the overlap by the probability of the conditioning event.","$1/$2","Intersection P(A and B)","0.12","Condition P(B)","0.3"),
    N(al_probability_2, "Trees, Venn diagrams and events","Use P(A or B)=P(A)+P(B)-P(A and B). Mutually exclusive events have zero overlap.","For a tree, multiply along a path and sum the paths that produce the same event.","Machine A makes 60%, with 2% defective. B makes 40%, with 5% defective.\nP(defect)=0.6*0.02+0.4*0.05=0.032.")
};

static const Topic al_dist[] = {
    F3(al_dist_1, "Binomial distribution","For X~B(n,p), fixed trials are independent with constant success probability p. Mean=np, variance=np(1-p).","Enter n, r and p to calculate P(X=r). For ranges, sum masses or use complements.","binom($1,$2,$3)","Trials n","12","Successes r","3","Probability p","0.2"),
    F3(al_dist_2, "Normal distribution","A normal model is symmetric about its mean. Tail probabilities use the standard normal distribution after standardising.","Compute z=(x-mu)/sigma, then evaluate P(Z<=z). Enter standard deviation, not variance.","norm(($1-$2)/$3)","Threshold x","115","Mean","100","Standard deviation","15")
};

static const Topic al_testing[] = {
    N(al_testing_1, "Binomial hypothesis tests","State H0 and H1 in terms of population probability p. Choose the tail direction from H1.","Under H0 compute the probability at least as extreme as the observation. Compare with the significance level.","H0:p=0.5, H1:p>0.5. In 10 trials observe 9 successes.\nP(X>=9)=11/1024, about 0.0107.\nAt 5%, reject H0."),
    N(al_testing_2, "Correlation and normal mean tests","Test correlation using the supplied critical value, or test a normal mean using the sampling SD sigma/sqrt(n).","State the alternative and match one- or two-tailed probability. Conclude in the context of the claim.","For H0:mu=50, sigma=8, n=16 and sample mean 54, z=(54-50)/2=2. A two-tailed p-value is about 0.0455.")
};

static const Topic al_units[] = {
    C(al_units_1, "SI units and modelling","Use metres, seconds, kilograms and newtons. Particle, light string and smooth surface are common modelling assumptions.","Convert into consistent units before substituting. A speed in km/h is divided by 3.6 for m/s.",Calculate,"Unit conversion calculation","72/3.6")
};

static const Topic al_motion[] = {
    F3(al_motion_1, "Constant acceleration","SUVAT applies for constant acceleration along a line. Choose a positive direction before using signed quantities.","To get displacement from u, a and t, use s=ut+at^2/2.","$1*$3+$2*$3^2/2","Initial velocity u","4","Acceleration a","3","Time t","5"),
    N(al_motion_2, "Variable acceleration","v=ds/dt and a=dv/dt. Integrate to recover v or s from their rates of change.","Use initial conditions to determine integration constants. Split the interval at v=0 when finding distance.","a=6t, v(0)=2.\nv=3t^2+2. Then s=t^3+2t if s(0)=0."),
    N(al_motion_3, "Projectiles","Horizontal motion has constant velocity while vertical acceleration is -g, neglecting air resistance.","Resolve initial velocity, solve the vertical motion for time and substitute in horizontal motion.","For launch speed u at angle theta, return to the initial height at t=2u*sin(theta)/g. Range = u^2*sin(2theta)/g.")
};

static const Topic al_forces[] = {
    F2(al_forces_1, "Newton's laws","A resultant force causes acceleration: F=ma. Weight equals mg. Equilibrium has zero resultant force.","Draw a force diagram and resolve along chosen axes. Divide the signed resultant by mass.","$1/$2","Resultant force (N)","18","Mass (kg)","4"),
    N(al_forces_2, "Friction, slopes and connected bodies","Friction opposes sliding tendency. Limiting friction equals mu*R. A light inextensible string gives equal acceleration magnitudes.","Resolve parallel and normal to the plane. For connected bodies write F=ma for each and eliminate the common tension.","A 5 kg block slides down a 30 degree slope with mu=0.2.\na=g(sin 30 - 0.2 cos 30), about 3.20 m/s^2 for g=9.8.")
};

static const Topic al_moments[] = {
    F2(al_moments_1, "Moments and rigid body equilibrium","Moment = force times perpendicular distance to the pivot. Equilibrium means zero resultant force and moment.","Use clockwise and anticlockwise signs. Choose the pivot at an unknown reaction to eliminate its moment.","$1*$2","Force (N)","60","Perpendicular arm (m)","0.35")
};

static const Chapter ig[] = {
    CH("Number",ig_number), CH("Equations and formulae",ig_algebra), CH("Sequences and graphs",ig_graphs),
    CH("Geometry and trigonometry",ig_geometry), CH("Vectors and transformations",ig_vectors), CH("Statistics and probability",ig_stats)
};
static const Chapter ocr[] = {
    CH("Algebra",ocr_algebra), CH("Enumeration",ocr_counting), CH("Coordinate geometry",ocr_coords),
    CH("Pythagoras and trigonometry",ocr_trig), CH("Calculus",ocr_calc), CH("Numerical methods",ocr_numerical),
    CH("Exponentials and logarithms",ocr_exponent)
};
static const Chapter al[] = {
    CH("Pure: Proof",al_proof), CH("Pure: Algebra and functions",al_algebra), CH("Pure: Coordinate geometry",al_coord),
    CH("Pure: Sequences and series",al_series), CH("Pure: Trigonometry",al_trig), CH("Pure: Exponentials and logs",al_logs),
    CH("Pure: Differentiation",al_diff), CH("Pure: Integration",al_integral), CH("Pure: Numerical methods",al_numerical),
    CH("Pure: Vectors",al_vectors), CH("Stats: Sampling and data set",al_sampling), CH("Stats: Data presentation",al_data),
    CH("Stats: Probability",al_probability), CH("Stats: Distributions",al_dist), CH("Stats: Hypothesis testing",al_testing),
    CH("Mechanics: Units and models",al_units), CH("Mechanics: Kinematics",al_motion),
    CH("Mechanics: Forces and Newton",al_forces), CH("Mechanics: Moments",al_moments)
};
#include "aqa_catalog.inc"

const Course courses[] = {
    {"Edexcel IGCSE Maths A","4MA1",ig,COUNT(ig)},
    {"OCR Level 3 Additional Maths","6993",ocr,COUNT(ocr)},
    {"Edexcel A Level Maths","9MA0",al,COUNT(al)},
    {"AQA Physics","8463",aqa_physics,COUNT(aqa_physics)},
    {"AQA Biology","8461",aqa_biology,COUNT(aqa_biology)},
    {"AQA Chemistry","8462",aqa_chemistry,COUNT(aqa_chemistry)}
};
const int course_count = COUNT(courses);
