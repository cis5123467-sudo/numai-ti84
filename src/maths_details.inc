/* Revision notes and additional examples. Each example ends in its result. */
#define DETAIL(id,a,b,c,d,t1,w1,t2,w2) \
    static const MathsDetail id = { "- " a "\n\n- " b "\n\n- " c "\n\n- " d, {{t1,w1},{t2,w2}} }

DETAIL(ig_number_1,
 "Prime numbers have exactly two positive factors. 1 is neither prime nor composite.",
 "Break both integers into prime powers. For HCF take the smaller power of each shared prime.",
 "For LCM take the greatest power of every prime that appears. For positive integers HCF*LCM = product.",
 "Use HCF for equal group sizes and LCM for the first time that repeating schedules coincide.",
 "HCF and LCM of 36 and 90","36=2^2*3^2 and 90=2*3^2*5.\nHCF=2*3^2=18.\nLCM=2^2*3^2*5=180.\nCheck: 18*180=36*90.",
 "When two alarms coincide","Alarms ring every 18 and 24 min.\n18=2*3^2, 24=2^3*3.\nLCM=2^3*3^2=72.\nThey next ring together after 72 min.");

DETAIL(ig_number_2,
 "Use a common denominator for addition and subtraction. Keep the value of each fraction unchanged when scaling it.",
 "For products, multiply numerators and denominators. Cancel factors before multiplying to keep numbers small.",
 "Convert mixed numbers to improper fractions before multiplying or dividing. Divide by multiplying by the reciprocal.",
 "For a recurring decimal, subtract two shifts with matching recurring tails. Distinguish 0.16 recurring from an exact 0.16.",
 "Divide mixed numbers","1 3/4 divided by 2/3 = 7/4 * 3/2.\nMultiply: 21/8.\nConvert back: 2 5/8.",
 "Recurring 0.1666...","Let x=0.1666...\n10x=1.666... and 100x=16.666...\nSubtract: 90x=15.\nSo x=1/6.");

DETAIL(ig_number_3,
 "For a nonzero common base: a^m*a^n=a^(m+n), a^m/a^n=a^(m-n), and a^0=1.",
 "A negative index gives a reciprocal. The denominator of a fractional index tells you which root to take.",
 "Extract square factors from a radical. Add only like surds after simplifying each one.",
 "To remove a binomial surd denominator multiply top and bottom by its conjugate, using a^2-b^2.",
 "Negative fractional power","Evaluate 27^(-2/3).\nCube root of 27 = 3.\nSquare to get 9, then take the reciprocal.\nAnswer: 1/9.",
 "Simplify and rationalise","sqrt(48)+sqrt(27)=4sqrt(3)+3sqrt(3).\nSo the sum is 7sqrt(3).\nFor 5/sqrt(3), multiply top and bottom by sqrt(3).\nAnswer: 5sqrt(3)/3.");

DETAIL(ig_number_4,
 "Union means in either set or both. Intersection means in both at once. A complement includes everything outside the set.",
 "The universal set fixes the total. A subset has every element in the larger set.",
 "Fill the overlap first, subtract it from each set total, then complete the outside.",
 "If the question says exactly one, use the two exclusive regions. If it says at least one, include the overlap.",
 "Find the overlap","40 pupils: 23 take French, 16 Spanish, 7 neither.\nUnion=40-7=33.\nOverlap=23+16-33=6.\nExactly one=33-6=27.",
 "Probability from a Venn diagram","Of 30 people, 12 cycle, 15 walk and 5 do both.\nCycle only=12-5=7; walk only=10.\nExactly one has probability (7+10)/30=17/30.");

DETAIL(ig_number_5,
 "Percentage change = change/original*100. For a percentage of an amount divide the percentage by 100 first.",
 "Use multipliers for increases and decreases. Successive changes multiply; an equal rise and fall do not cancel.",
 "Reverse a change by dividing by the original multiplier. The final price is the new percentage of the starting price.",
 "Compound interest grows with each period; simple interest uses the original principal every period.",
 "Reverse a discount","A 15% discount leaves GBP 68.\nSale price = 0.85 * original.\nOriginal = 68/0.85 = GBP 80.",
 "Successive changes","GBP 200 rises 10%, then falls 20%.\n200*1.10*0.80=GBP 176.\n176/200=0.88, so the overall decrease is 12%.");

DETAIL(ig_number_6,
 "Write ratio quantities in the same units. Divide all terms by a common factor to simplify.",
 "For sharing, add the ratio parts and divide the total by that sum to find one part.",
 "If only a difference is given, divide by the difference between the two ratio parts.",
 "For direct scaling use the same multiplier on both quantities. For fixed work, more equally productive workers means less time.",
 "Share from a difference","A:B=7:4 and A has 18 more than B.\nThree parts=18, so one part=6.\nA=42, B=24, total=66.",
 "Mixing ratios","Paint:water=5:2 in a 2.1 L mixture.\nOne part=2.1/7=0.3 L.\nPaint=1.5 L, water=0.6 L.");

DETAIL(ig_number_7,
 "When rounded to the nearest unit u, use lower=shown-u/2 and upper=shown+u/2 for positive quantities.",
 "Use the precision actually given: nearest 10, nearest 0.1 and significant figures imply different intervals.",
 "For positive values, maximise a product with both upper bounds; maximise a quotient with upper numerator and lower denominator.",
 "For a difference, use upper first quantity minus lower second for its upper bound. Round a final estimate only after calculating.",
 "Upper bound for speed","Distance 150 m to nearest 10 m. Time 20 s to nearest second.\nUpper distance 155; lower time 19.5.\nUpper speed bound=155/19.5=7.9487... m/s.",
 "Minimum area bound","Lengths 8.2 cm and 3.0 cm, both to nearest 0.1.\nLower sides=8.15 and 2.95.\nLower area=8.15*2.95=24.0425 cm^2.");

DETAIL(ig_number_8,
 "Standard form is a*10^n with 1<=a<10 and integer n. Small numbers between zero and one have negative exponents.",
 "In a product add powers of ten; in a quotient subtract them. Renormalise the coefficient at the end.",
 "For addition or subtraction first use a common power of ten, then combine coefficients.",
 "Check that magnitude agrees with the original problem. Moving the decimal left in a coefficient increases the exponent.",
 "Normalise a product","(8*10^4)(7*10^3)=56*10^7.\nRewrite 56 as 5.6*10.\nAnswer: 5.6*10^8.",
 "Add different powers","3.2*10^-4 + 4*10^-5.\nUse 4*10^-5=0.4*10^-4.\nSum=(3.2+0.4)*10^-4=3.6*10^-4.");

DETAIL(ig_number_9,
 "Speed is distance/time; density is mass/volume; pressure is force/area. Choose units before substituting.",
 "An average speed uses total distance divided by total time. Averaging separate speeds rarely gives the right answer.",
 "Change hours and minutes to one time unit. Square or cube the length conversion for areas and volumes.",
 "Use brackets around compound numerators and denominators. Keep the full calculator result until the final rounding.",
 "Average journey speed","Travel 30 km in 0.5 h, then 30 km in 1 h.\nTotal distance=60 km; time=1.5 h.\nAverage speed=40 km/h.",
 "Density and units","A solid has mass 540 g and volume 200 cm^3.\nDensity=2.7 g/cm^3.\nSince 1 g/cm^3=1000 kg/m^3, this is 2700 kg/m^3.");

DETAIL(ig_algebra_1,
 "A term is separated by addition or subtraction. Like terms have the same variables raised to the same powers.",
 "Multiply each term in one bracket by each term in the other, including signs.",
 "To factorise, look first for a shared numerical or algebraic factor. Check by expanding.",
 "Rearrange formulae by applying the same operation to both sides. Write any denominator restriction.",
 "Expand two brackets","(2x-3)(x+4)=2x^2+8x-3x-12.\nCollect the x terms.\nAnswer: 2x^2+5x-12.",
 "Change the subject","Make h the subject of A=(a+b)h/2.\nMultiply by 2: 2A=(a+b)h.\nDivide: h=2A/(a+b), for a+b != 0.");

DETAIL(ig_algebra_2,
 "Expand brackets and clear fractions before collecting terms. Multiply every term by the common denominator.",
 "Move variable terms to one side and constants to the other by adding or subtracting equally.",
 "Divide by the final coefficient. If the variable cancels, check whether the remaining statement is true or impossible.",
 "Substitute your solution back into the original equation to catch omitted signs or terms.",
 "Equation with brackets","3(2x-1)=4x+9.\n6x-3=4x+9, so 2x=12.\nx=6. Both sides give 33.",
 "Equation with fractions","(x+1)/3 - x/2 = 2.\nMultiply by 6: 2(x+1)-3x=12.\n2-x=12, hence x=-10.");

DETAIL(ig_algebra_3,
 "First put all terms on one side to obtain ax^2+bx+c=0. Check that a is nonzero.",
 "When factorising, set each factor equal to zero separately. Both can give valid roots.",
 "Use x=(-b +/- sqrt(b^2-4ac))/(2a) when factoring is inconvenient. Keep both signs.",
 "The discriminant gives two, one repeated, or no real roots as it is positive, zero, or negative.",
 "Factor a non-monic quadratic","3x^2+x-2=0.\n(3x-2)(x+1)=0.\n3x-2=0 or x+1=0.\nAnswer: x=2/3 or -1.",
 "Roots in exact form","x^2+2x-5=0.\nDiscriminant=4+20=24.\nx=(-2 +/- sqrt(24))/2.\nAnswer: x=-1 +/- sqrt(6).");

DETAIL(ig_algebra_4,
 "Translate 'directly proportional to x^n' as y=k*x^n; 'inversely proportional' as y=k/x^n.",
 "Use the given pair of values to find k, then write the complete equation.",
 "A factor of p in x gives factor p^n for direct proportion or 1/p^n for inverse proportion.",
 "Check sensible domains and units. In an inverse model x cannot be zero.",
 "Inverse square model","y is inverse to x^2; y=12 when x=2.\n12=k/4, so k=48.\nAt x=4, y=48/16=3.",
 "Direct root proportion","y=k*sqrt(x), and y=15 at x=9.\nk=15/3=5.\nAt x=49, y=5*7=35.");

DETAIL(ig_algebra_5,
 "For elimination make one variable's coefficients equal, then subtract, or opposite, then add.",
 "Substitution is convenient when one equation already isolates a variable.",
 "For a line and curve, substitute the line to obtain a polynomial. Return every valid pair.",
 "Check each pair in both original equations. Parallel distinct lines give no solution.",
 "Eliminate y","3x+2y=13 and 2x-y=4.\nDouble the second: 4x-2y=8.\nAdd to get 7x=21.\nx=3, and y=2.",
 "Intersect a line and parabola","y=x+2 and y=x^2.\nx^2-x-2=(x-2)(x+1)=0.\nx=2 or -1. Substitute in the line.\nIntersections: (2,4) and (-1,1).");

DETAIL(ig_algebra_6,
 "Keep the inequality direction when adding or subtracting. Reverse it when multiplying or dividing by a negative number.",
 "Use an open endpoint for < or > and a filled endpoint for <= or >=.",
 "For a quadratic, transfer terms to one side, find the roots, and test signs between and beyond the roots.",
 "On a coordinate graph shade the half-plane that satisfies the inequality. Use a test point away from its boundary.",
 "Double inequality","Solve -5 < 3x+1 <= 10.\nSubtract 1 from all three parts: -6 < 3x <= 9.\nDivide by 3: -2 < x <= 3.",
 "Quadratic inequality","x^2-x-6>0 becomes (x-3)(x+2)>0.\nFactors have the same sign outside the roots.\nAnswer: x<-2 or x>3.");

DETAIL(ig_graphs_1,
 "For an arithmetic sequence, term n = a+(n-1)d. Include (n-1) because term 1 already equals a.",
 "For a quadratic sequence, its constant second difference is twice the coefficient of n^2.",
 "Subtract that quadratic part to find a linear remainder, then add the two rules.",
 "Check the term number is a positive integer when deciding if a value occurs in a sequence.",
 "Find a quadratic nth term","Terms 4, 9, 16, 25.\nSecond difference=2, so start with n^2.\nRemainders 3,5,7,9 give 2n+1.\nRule: n^2+2n+1.",
 "Is 95 a term?","Sequence 8,13,18,... has term 5n+3.\n5n+3=95 gives n=18.4.\nThe index is not an integer, so 95 is absent.");

DETAIL(ig_graphs_2,
 "Domain means allowed inputs; range means possible outputs. Denominators and square roots can restrict the domain.",
 "In f(g(x)) apply g first. Reversing the order generally produces a different rule.",
 "Find an inverse by writing y=f(x), isolating x, and swapping the variable labels.",
 "An inverse that is a function needs a one-to-one branch. Choose the branch before taking a square root.",
 "Order of composition","f(x)=2x+1 and g(x)=x^2.\nf(g(3))=f(9)=19.\ng(f(3))=g(7)=49.\nThe order changes the result.",
 "Invert a restricted square","f(x)=x^2+3 for x>=0.\ny-3=x^2. Take the nonnegative root.\nf^(-1)(x)=sqrt(x-3), with x>=3.");

DETAIL(ig_graphs_3,
 "For y=mx+c, m is rise/run and c is the y-intercept. Parallel lines have the same gradient.",
 "Set x=0 for a y-intercept and y=0 for x-intercepts. Intersections satisfy both equations.",
 "Use distance-time gradient for speed. A horizontal distance-time segment represents rest.",
 "Read axis scales before taking coordinates; for a smooth curve use a tangent for its instantaneous gradient.",
 "Line through two points","A=(1,5), B=(4,11).\nm=(11-5)/(4-1)=2.\n5=2*1+c, so c=3.\nLine: y=2x+3.",
 "Intersect straight lines","y=3x-2 and y=x+6.\nSet equal: 2x=8, so x=4.\nThen y=10.\nIntersection: (4,10).");

DETAIL(ig_graphs_4,
 "The derivative gives the tangent gradient. For ax^n, multiply by n and reduce the power by one.",
 "Differentiate each term independently. Constants contribute zero.",
 "Set f'(x)=0 to find stationary x-values, then substitute in f for their coordinates.",
 "Classify using signs of f' on either side: + to - gives a maximum; - to + gives a minimum.",
 "Minimum of a quadratic","f=x^2-6x+11.\nf'=2x-6=0 at x=3.\nf(3)=2; f' changes from - to +.\nMinimum at (3,2).",
 "Gradient at a point","For y=2x^3-x, dy/dx=6x^2-1.\nAt x=-2, gradient=6*4-1=23.\nThe negative x is squared before multiplying.");

DETAIL(ig_geometry_1,
 "Angles on a straight line sum to 180 degrees; around a point they sum to 360. Opposite angles at a crossing are equal.",
 "In parallel lines, corresponding and alternate angles match; co-interior angles add to 180.",
 "Triangle angles sum to 180. In an isosceles triangle, angles opposite the equal sides are equal.",
 "Give the rule after each angle calculation. Check that lines really are parallel before using parallel-line facts.",
 "Isosceles base angles","An isosceles triangle has vertex angle 38 degrees.\nBase angles share 180-38=142.\nEach base angle is 71 degrees.",
 "Exterior angle at a triangle","Two remote interior angles are 47 and 68 degrees.\nAdjacent interior angle=180-47-68=65.\nExterior angle=180-65=115 degrees.");

DETAIL(ig_geometry_2,
 "Interior angle sum of an n-gon is (n-2)*180 degrees, found by splitting it into triangles.",
 "Exterior turns around a convex polygon add to 360. For a regular polygon each exterior angle is 360/n.",
 "An interior and its matching exterior angle add to 180. Use the exterior angle to recover n.",
 "Line symmetry is reflection. Rotational symmetry counts the distinct positions matching during one full turn.",
 "Find the number of sides","A regular polygon has interior angle 156 degrees.\nExterior=180-156=24.\nn=360/24=15 sides.",
 "Missing pentagon angle","Four angles total 438 degrees.\nPentagon sum=(5-2)*180=540.\nMissing angle=540-438=102 degrees.");

DETAIL(ig_geometry_3,
 "A bearing is measured clockwise from north and written with three digits. A reverse bearing differs by 180 degrees.",
 "For scales, match units first. A 1:n drawing means one unit on paper represents n units in real life.",
 "A perpendicular bisector is the locus equidistant from two points. An angle bisector gives equal perpendicular distances to the two arms.",
 "Use ruler and compasses for construction, leave construction arcs, and respect strict versus inclusive boundaries.",
 "Reverse a bearing","B is at bearing 065 degrees from A.\nThe return direction is opposite.\n065+180=245 degrees from B to A.",
 "Convert a map length","On a 1:50,000 map the route is 7.6 cm.\nReal length=380000 cm=3800 m.\nAnswer: 3.8 km.");

DETAIL(ig_geometry_4,
 "For the same arc, angle at the centre is twice the angle at the circumference. Angles in the same segment are equal.",
 "An angle in a semicircle is 90 degrees. Opposite angles of a cyclic quadrilateral add to 180.",
 "A tangent is perpendicular to the radius at contact. Two tangents from one exterior point have equal lengths.",
 "Use the alternate segment theorem for a tangent-chord angle. Name the chord or arc used in your reason.",
 "Cyclic quadrilateral","Opposite angles are (2x+10) and (x+20) degrees.\n3x+30=180, giving x=50.\nThe two angles are 110 and 70 degrees.",
 "Tangents from one point","PA and PB touch the circle; angle APB=50 degrees.\nOAP and OBP are each 90 degrees.\nAngle AOB=360-180-50=130 degrees.");

DETAIL(ig_geometry_5,
 "Congruent shapes have the same size and shape. Use SSS, SAS, ASA or right angle-hypotenuse-side.",
 "For SAS the angle must be between the two listed sides. Three equal angles alone prove similarity.",
 "For similarity establish matching angles or consistent corresponding side ratios.",
 "Label corresponding vertices in the same order, then justify any equal lengths or angles you infer.",
 "Prove two triangles congruent","AB=AD, BC=DC and AC is shared.\nTriangles ABC and ADC have three matching sides.\nBy SSS they are congruent, so angle BAC=CAD.",
 "Use parallel lines for similarity","D on AB, E on AC, and DE parallel to BC.\nAngles ADE and ABC match; AED and ACB match.\nADE and ABC are similar by AA.");

DETAIL(ig_geometry_6,
 "Pythagoras applies to right triangles. Work out the hypotenuse by adding leg squares and taking the positive root.",
 "To find a leg, subtract the other leg's square from the hypotenuse square.",
 "Choose sin, cos or tan from the sides involved relative to the named angle. Opposite and adjacent change with the chosen angle.",
 "Use inverse trig for an angle and degrees for GCSE questions unless stated otherwise.",
 "Find a leg","A ladder is 13 m and its foot is 5 m from the wall.\nHeight^2=13^2-5^2=144.\nHeight=12 m.",
 "Find an angle of elevation","Rise=4 m and horizontal run=7 m.\ntan(theta)=4/7.\ntheta=atan(4/7)=29.7 degrees to 1 dp.");

DETAIL(ig_geometry_7,
 "Use a/sin A=b/sin B when you have an opposite side-angle pair. Label sides opposite their angles.",
 "Use cosine rule for two sides and the included angle, or for an angle from three sides.",
 "For a missing angle by sine rule, consider theta and 180-theta. Discard angles that cannot fit the triangle.",
 "Use area=0.5*a*b*sin C with the included angle C. Keep calculator values until final rounding.",
 "Find an angle from three sides","a=7, b=8, c=9.\ncos C=(49+64-81)/(2*7*8)=2/7.\nC=acos(2/7)=73.4 degrees (1 dp).",
 "Find a side by sine rule","A=35 degrees, B=65 degrees, a=8 cm.\nb/ sin(65)=8/ sin(35).\nb=8*sin(65)/sin(35)=12.64 cm to 2 dp.");

DETAIL(ig_geometry_8,
 "Circle circumference is 2*pi*r and area is pi*r^2. Convert diameter to radius first.",
 "An arc or sector with central angle theta degrees is theta/360 of the corresponding full circle measure.",
 "Sector perimeter includes two straight radii as well as its arc. A segment's area is sector area minus triangle area for a minor segment.",
 "Keep exact multiples of pi when requested; otherwise round only the final result.",
 "Arc and sector perimeter","Radius 6 cm and angle 120 degrees.\nArc=(120/360)*12*pi=4*pi cm.\nPerimeter=12+4*pi cm.",
 "Area of a circular segment","Radius 8 cm and angle 90 degrees.\nSector area=16*pi cm^2.\nTriangle area=0.5*8*8=32 cm^2.\nSegment area=16*pi-32 cm^2.");

DETAIL(ig_geometry_9,
 "A prism's volume is cross-sectional area times length. A cylinder is a prism with circular cross-section.",
 "A cone or pyramid is one third of the related prism's volume. Use perpendicular height for volume.",
 "Surface area sums the exposed faces. Cylinder curved area is circumference times height; cone curved area uses slant height.",
 "Use squared units for areas and cubed units for volumes. Use 1 cm^3=1 mL and 1000 cm^3=1 L.",
 "Cylinder surface area","Radius 3 cm, height 10 cm.\nTwo ends=2*pi*3^2=18*pi.\nCurved area=2*pi*3*10=60*pi.\nTotal=78*pi cm^2.",
 "Volume of a cone","Radius 4 cm and perpendicular height 9 cm.\nV=pi*4^2*9/3=48*pi cm^3.\nThe slant height plays no part in this volume.");

DETAIL(ig_geometry_10,
 "Corresponding lengths of similar figures have a constant ratio k. Match the small side to the correct large one.",
 "Area ratio is k^2 and volume ratio is k^3. Take square or cube roots to recover a length ratio.",
 "Convert lengths to the same units before finding k. Keep scale direction consistent.",
 "Similarity gives matching angles and proportional sides. Congruence is the special case k=1.",
 "Find length scale from area","Areas are 32 and 72 cm^2.\nArea ratio=72/32=9/4.\nLength factor=sqrt(9/4)=3/2.\nA 6 cm side becomes 9 cm.",
 "Compare volumes","A similar model is enlarged by factor 2.5.\nThe original is 32 cm^3.\nNew volume=32*2.5^3=500 cm^3.");

DETAIL(ig_vectors_1,
 "A vector has magnitude and direction. A column vector records horizontal and vertical components.",
 "AB=OB-OA. To follow successive paths add the vectors. Reversing a vector changes both signs.",
 "Multiply components by a scalar. Parallel vectors are scalar multiples, including negative multiples.",
 "Use sqrt(x^2+y^2) for magnitude. To prove three points collinear show two displacement vectors on their common line are scalar multiples.",
 "Displacement and length","A=(2,-1) and B=(-1,3).\nAB=(-1-2,3-(-1))=(-3,4).\nLength=sqrt(9+16)=5.",
 "Prove points collinear","P=(1,2), Q=(3,5), R=(7,11).\nPQ=(2,3), PR=(6,9)=3*PQ.\nThey share starting point P, so P,Q,R are collinear.");

DETAIL(ig_vectors_2,
 "Describe a translation with a vector and a reflection with the exact mirror-line equation.",
 "Describe a rotation with centre, angle and direction. Corresponding points are the same distance from the centre.",
 "For enlargement, multiply each displacement from the centre by the scale factor. Negative factors put the image on the opposite side.",
 "Apply successive transformations in order. Only enlargement changes lengths when its scale magnitude differs from one.",
 "Rotate about the origin","Rotate (4,1) 90 degrees anticlockwise around (0,0).\nThe rule is (x,y)->(-y,x).\nImage=(-1,4).",
 "Reflect in y=x","Reflect (-2,5) in y=x by swapping its coordinates.\nImage=(5,-2).\nTheir midpoint is (1.5,1.5), on the mirror line.");

DETAIL(ig_stats_1,
 "Use bar charts for categories, histograms for continuous grouped data and cumulative frequency to read percentiles.",
 "In a histogram, bar area represents frequency. Height is frequency density=frequency/class width.",
 "Use class upper boundaries for cumulative frequencies. Read Q1, median and Q3 at N/4, N/2 and 3N/4.",
 "Describe correlation by strength and direction. A line of best fit supports interpolation within the data range.",
 "Work backwards from a histogram","The 20 to 28 class has density 3.5.\nClass width=8.\nFrequency=8*3.5=28.",
 "Interpret a cumulative curve","There are 80 items.\nRead the values at ranks 20, 40 and 60.\nIf they are 12, 17 and 25, median=17 and IQR=25-12=13.");

DETAIL(ig_stats_2,
 "Mean is sum divided by count. Median uses the middle position; mode is the most frequent value or class.",
 "In a frequency table use sum(f*x)/sum(f). For grouped data use midpoints, so the mean is an estimate.",
 "Range is max minus min. IQR is Q3-Q1 and describes the spread of the middle half.",
 "Compare both centre and spread in context. Outliers change the mean and range more than the median.",
 "Weighted mean","Scores 2, 5, 9 occur 4, 3, 1 times.\nTotal=2*4+5*3+9=32.\nMean=32/(4+3+1)=4.",
 "Compare median and mean","Data: 1, 2, 3, 4, 20.\nMedian=3; mean=30/5=6; range=19.\nThe high value 20 pulls the mean above the median.");

DETAIL(ig_stats_3,
 "Probabilities run from 0 to 1. The complement has probability 1-P(event).",
 "Multiply probabilities along one tree path. Add the relevant disjoint paths.",
 "With replacement, the second draw has unchanged probabilities. Without replacement, adjust the total and the selected category.",
 "For mutually exclusive events use addition. Independent events can occur together and have product probabilities.",
 "Exactly one red draw","Bag: 3 red, 2 blue; two draws without replacement.\nRB=(3/5)(2/4)=3/10.\nBR=(2/5)(3/4)=3/10.\nExactly one red=3/5.",
 "At least one six","Two independent fair dice.\nP(no six)=(5/6)^2=25/36.\nP(at least one six)=1-25/36=11/36.");

DETAIL(ocr_algebra_1,
 "Expand and arrange polynomials in descending powers. Include a zero placeholder for absent powers in long division.",
 "When dividing by x-r, the remainder is f(r), and x-r is a factor exactly when f(r)=0.",
 "If dividing by ax-b, test r=b/a. After finding a root, divide it out to reduce the degree.",
 "Check quotient and remainder by reconstructing dividend = divisor*quotient + remainder.",
 "Factor a cubic","f=x^3-4x^2+x+6.\nf(2)=8-16+2+6=0.\nDivide by x-2: quotient x^2-2x-3.\nAnswer: (x-2)(x-3)(x+1).",
 "Find a remainder","Divide x^3+2x-5 by x+1.\nUse r=-1: f(-1)=-1-2-5.\nRemainder=-8.\nCheck: (x+1)(x^2-x+3)-8=f(x).");

DETAIL(ocr_algebra_2,
 "Factor each denominator to find a common denominator. Exclude inputs that make any original denominator zero.",
 "Cancel common factors across a product only. Terms in a sum cannot be cancelled separately.",
 "Extract square factors and collect like radicals. Multiply or divide radicals before extracting where useful.",
 "Rationalise a sum in a denominator using its conjugate, then simplify the numerator and the rational denominator.",
 "Add algebraic fractions","1/(x-2)+2/(x+2).\nUse denominator (x-2)(x+2).\nNumerator=x+2+2(x-2)=3x-2.\nAnswer: (3x-2)/(x^2-4), x != +/-2.",
 "Rationalise a binomial","3/(2+sqrt(3)).\nMultiply by (2-sqrt(3))/(2-sqrt(3)).\nDenominator=4-3=1.\nAnswer: 6-3sqrt(3).");

DETAIL(ocr_algebra_3,
 "For ax^2+bx+c, factor a from the x terms and halve b/a. Write h=b/(2a).",
 "Then ax^2+bx+c=a(x+h)^2+c-a*h^2. The turning point is (-h,c-a*h^2).",
 "Positive a gives a minimum and negative a gives a maximum. The line of symmetry is x=-h.",
 "To solve a quadratic this way isolate the square before taking square roots. Include both signs.",
 "Find a maximum","-x^2+8x-11=-(x-4)^2+16-11.\nThe square is smallest at x=4.\nMaximum point: (4,5).",
 "Solve by completing the square","2x^2+4x-6=0. Divide by 2.\nx^2+2x-3=(x+1)^2-4.\n(x+1)^2=4, so x+1=+/-2.\nx=1 or -3.");

DETAIL(ocr_algebra_4,
 "Translate the unknown and any constraints first. Collect every polynomial term on one side.",
 "Use factorisation, the quadratic formula or completing the square for a quadratic.",
 "For a cubic, test for rational roots and divide out each known factor. Solve the remaining quadratic.",
 "For simultaneous equations eliminate or substitute. Check candidate roots in the original model.",
 "Solve a cubic","x^3+x^2-4x-4=0.\nGroup: x^2(x+1)-4(x+1)=0.\n(x+1)(x-2)(x+2)=0.\nx=-2,-1,2.",
 "Reject an impossible length","A rectangle is x by x+3 with area 40.\nx^2+3x-40=(x+8)(x-5)=0.\nRoots -8 and 5. Only x=5 is a length.\nSides: 5 and 8.");

DETAIL(ocr_algebra_5,
 "Reverse an inequality when multiplying or dividing by a negative number.",
 "For a quadratic inequality, locate the roots and test signs in the resulting intervals.",
 "Plot each linear boundary. A dashed boundary is excluded and a solid boundary is allowed.",
 "Test a point to choose each half-plane. The solution region is the intersection of all required half-planes.",
 "Find a quadratic interval","2x^2-5x+2<0.\nFactor: (2x-1)(x-2)<0.\nLeading coefficient is positive; signs differ between roots.\nSolution: 1/2<x<2.",
 "Select a half-plane","For 2x+y<=6, plot through (0,6) and (3,0).\nAt (0,0), 0<=6 is true.\nShade the origin side; keep the line solid.");

DETAIL(ocr_algebra_6,
 "A recurrence uses earlier terms, so state the initial value and which index it belongs to.",
 "For u(n+1)=a*u(n)+b, a fixed point L satisfies L=aL+b. Finding L alone does not prove convergence.",
 "If |a|<1, the error u(n)-L shrinks by factor |a| each step. Negative a makes the error alternate in sign.",
 "When modelling, relate the multiplier and addition to the real context and check that values stay meaningful.",
 "Compute successive terms","u(0)=2 and u(n+1)=3u(n)-1.\nu(1)=5, u(2)=14, u(3)=41.\nUse the latest term at each substitution.",
 "Find a long-term balance","b(0)=0, b(n+1)=0.75b(n)+20.\nL=0.75L+20 gives L=80.\nError multiplies by 0.75, so the sequence approaches 80.");

DETAIL(ocr_counting_1,
 "The x^r term in (a+bx)^n is nCr * a^(n-r) * b^r * x^r for a nonnegative integer n.",
 "Count the constant term as r=0. The term number is r+1.",
 "Use the sign of b throughout. For negative b, odd powers have a negative coefficient.",
 "Check that the powers of a and bx add to n in every term.",
 "Coefficient of x^3","In (2-3x)^5, choose r=3.\n5C3*2^2*(-3)^3=10*4*(-27).\nCoefficient=-1080.",
 "Expand a binomial","(1+2x)^3.\nCoefficients 1,3,3,1.\nMultiply by (2x)^r.\nAnswer: 1+6x+12x^2+8x^3.");

DETAIL(ocr_counting_2,
 "Use the product rule for sequential choices and add counts of disjoint cases.",
 "A two-way table records counts with two labels. Check that row totals and column totals agree.",
 "For overlapping sets, add the set sizes then subtract the overlap once.",
 "When an outcome needs a restriction, split into disjoint cases or subtract forbidden outcomes from the total.",
 "Codes without repetition","Use digits 1,2,3,4 to make a two-digit even code, without repeats.\nUnits digit: 2 options. Tens: 3 remaining.\nTotal=2*3=6.",
 "Count using the complement","Four binary choices give 2^4=16 outcomes.\nOnly one has no 1s, namely 0000.\nAt least one 1 occurs in 16-1=15 outcomes.");

DETAIL(ocr_counting_3,
 "Use nPr when positions or order distinguish outcomes. Use nCr when only membership matters.",
 "nPr=n!/(n-r)! and nCr=n!/(r!*(n-r)!). Treat 0!=1.",
 "For independent selections from different groups, multiply the counts.",
 "If there are several allowed group splits, count each split separately and add.",
 "Award different prizes","Award gold, silver and bronze to 8 people.\nThere are 8 then 7 then 6 choices.\n8P3=336.",
 "Choose a mixed committee","Choose 2 from 5 students and 1 from 4 staff.\n5C2=10 and 4C1=4.\nTotal=10*4=40 committees.");

DETAIL(ocr_counting_4,
 "Use X~B(n,p) for a fixed number of independent trials with a common success chance.",
 "P(X=r)=nCr*p^r*(1-p)^(n-r). The coefficient counts which trials succeed.",
 "For at most r, add probabilities for 0 to r. For at least one, subtract the zero-success probability from one.",
 "Check whether the question uses 'at least', 'at most' or 'exactly'. Without replacement, p generally changes.",
 "Exactly one success","Four independent attempts each have p=0.2.\nP(X=1)=4C1*0.2*0.8^3.\nAnswer: 0.4096.",
 "At least two successes","X~B(3,0.4).\nP(0)=0.6^3=0.216. P(1)=3*0.4*0.6^2=0.432.\nP(X>=2)=1-0.216-0.432=0.352.");

DETAIL(ocr_coords_1,
 "The gradient between A and B is change in y/change in x. A vertical line has undefined gradient.",
 "The midpoint averages each coordinate; the distance is the square root of the sum of squared coordinate changes.",
 "Use y-y1=m(x-x1). For a nonvertical perpendicular pair, gradients multiply to -1.",
 "A horizontal line and a vertical line are perpendicular. Handle those separately from the reciprocal rule.",
 "Midpoint and distance","A=(-2,1), B=(4,9).\nMidpoint=(1,5).\nChanges are 6 and 8, so distance=sqrt(36+64)=10.",
 "Perpendicular through a point","Given y=2x+7, perpendicular gradient=-1/2.\nThrough (4,3): y-3=-(x-4)/2.\nAnswer: y=-x/2+5.");

DETAIL(ocr_coords_2,
 "A circle has equation (x-a)^2+(y-b)^2=r^2. The centre is (a,b).",
 "To recover centre from an expanded equation complete the square in x and y separately.",
 "For a line intersection, substitute its equation and solve the resulting quadratic. One repeated root is tangency.",
 "A tangent is perpendicular to the radius at contact. A diameter's midpoint gives the centre.",
 "Circle with a given diameter","Diameter ends (-1,2) and (5,10).\nCentre=(2,6). Radius=sqrt(3^2+4^2)=5.\nEquation: (x-2)^2+(y-6)^2=25.",
 "Line and circle intersections","x^2+y^2=25 and y=3.\nx^2=25-9=16, so x=+/-4.\nPoints: (-4,3) and (4,3).");

DETAIL(ocr_coords_3,
 "Mark intercepts, discontinuities and asymptotes before drawing the curve.",
 "For a polynomial, use roots with their multiplicities, the leading term, and any stationary points.",
 "For trig graphs check period, amplitude and range. For exponentials note their horizontal asymptote.",
 "Read intersections to estimate solutions. Use an algebraic method if exact answers are required.",
 "Sketch a repeated root","y=x(x-2)^2. Roots are 0 and 2.\nAt x=0 it crosses; at x=2 it touches.\nLeading term x^3 makes the left end go down and right end go up.",
 "Sketch a shifted exponential","y=2^x-3.\nHorizontal asymptote y=-3; at x=0, y=-2.\nSet y=0: x=ln(3)/ln(2), about 1.585.");

DETAIL(ocr_coords_4,
 "Convert constraints to inequalities in x and y. Include x>=0 and y>=0 if quantities are nonnegative.",
 "Draw boundary lines and use a test point for the correct side. Find coordinates of all vertices.",
 "Evaluate the linear objective at each vertex of a closed bounded feasible region.",
 "If whole numbers are required, test suitable integer points. Rounding a continuous solution can break a constraint.",
 "Maximise an objective","x,y>=0, x+y<=8, y<=5. Maximise 2x+3y.\nCorners: (0,0),(8,0),(3,5),(0,5).\nValues: 0,16,21,15.\nMaximum 21 at (3,5).",
 "Integer constraint","Use integer x,y>=0 with 2x+3y<=7. Maximise x+2y.\nFor y=0,1,2 the best x is 3,2,0.\nObjectives: 3,4,4.\nMaximum 4 at (2,1) or (0,2).");

DETAIL(ocr_trig_1,
 "Find a horizontal diagonal first, then combine it with the perpendicular height. In a cuboid d=sqrt(l^2+w^2+h^2).",
 "For the angle with a plane, use the angle between the line and its projection onto the plane.",
 "For a line's steepest angle on a sloping plane, use the cross-section perpendicular to the horizontal contours.",
 "Sketch the relevant right triangle. Keep exact lengths until the final trig calculation.",
 "Space diagonal","Cuboid dimensions 2,3,6 cm.\nBase diagonal=sqrt(13).\nSpace diagonal=sqrt(13+36)=7 cm.",
 "Angle to the base","Base diagonal=8 m and rise=6 m.\ntan(theta)=6/8=0.75.\ntheta=36.9 degrees to 1 dp.");

DETAIL(ocr_trig_2,
 "Label each side by the angle opposite. Use the sine rule only with one known opposite pair.",
 "Use the cosine rule for SAS or SSS. In a side-length calculation choose the positive square root.",
 "Sine does not distinguish an angle from its supplement. Test both values against the triangle angle sum.",
 "The area is half the product of two sides and the sine of the angle between them.",
 "Cosine-rule side","a=5, b=7, included angle 60 degrees.\nc^2=25+49-2*5*7*0.5=39.\nc=sqrt(39), about 6.24.",
 "Ambiguous sine-rule angles","A=30 degrees, a=6, b=8.\nsin B=8*sin(30)/6=2/3.\nB is about 41.8 or 138.2 degrees.\nBoth leave C positive, so both fit.");

DETAIL(ocr_trig_3,
 "Use sin^2 x+cos^2 x=1 and tan x=sin x/cos x where cos x is nonzero.",
 "Sine and cosine repeat every 360 degrees; tangent repeats every 180.",
 "Find the principal value then other angles with the same sine or cosine by symmetry.",
 "For trig of kx, solve on the interval multiplied by k first, then divide all solutions by k.",
 "Solve tan(2x)=1","For 0<=x<180 degrees, 0<=2x<360.\n2x=45 or 225.\nx=22.5 or 112.5 degrees.",
 "Find all cos solutions","Solve cos x=-sqrt(3)/2 for 0<=x<360.\nReference angle 30 degrees. Cosine is negative in quadrants 2 and 3.\nx=150 or 210 degrees.");

DETAIL(ocr_calc_1,
 "A derivative is a rate of change. The gradient at a point comes from substituting its x-value after differentiating.",
 "For kx^n the derivative is n*k*x^(n-1). The derivative of a constant is zero.",
 "Expand polynomial products first when using the power rule.",
 "Gradient units are output units per input unit. A negative gradient means the output is decreasing locally.",
 "Differentiate a product by expansion","y=x^2(3x-2)=3x^3-2x^2.\ndy/dx=9x^2-4x.\nAt x=2, gradient=36-8=28.",
 "Find where a gradient is 6","f=x^3+3x.\nf'=3x^2+3. Set this to 6.\nSubtract 3 and divide by 3: x^2=1.\nThe gradient is 6 at both x=-1 and x=1.");

DETAIL(ocr_calc_2,
 "Calculate the contact point (a,f(a)) and the derivative f'(a).",
 "The tangent has gradient f'(a) and passes through the contact point.",
 "For a nonzero tangent gradient m, the normal has gradient -1/m. A horizontal tangent has a vertical normal.",
 "Use y-y1=m(x-x1) and check that the final line passes through the contact point.",
 "Tangent and normal to a cubic","y=x^3 at x=2 gives point (2,8).\nGradient=3*2^2=12.\nTangent: y-8=12(x-2).\nNormal: y-8=-(x-2)/12.",
 "Normal at a flat point","y=x^2+4x+3 at x=-2.\ny' = 2x+4=0 and y=-1.\nTangent y=-1; normal x=-2.");

DETAIL(ocr_calc_3,
 "Find stationary points by solving f'=0 and evaluating f at the solutions.",
 "If f''>0 there is a minimum; if f''<0 there is a maximum. If f''=0 use a sign test on f'.",
 "For a maximum or minimum on a closed interval compare interior stationary values and the endpoints.",
 "In word problems state the feasible domain and translate your mathematical result back into the context.",
 "Classify a pair of points","f=x^3-12x.\nf'=3x^2-12=0 at x=+/-2.\nf''=6x. Maximum (-2,16); minimum (2,-16).",
 "Optimise a rectangle","A rectangle with perimeter 24 has area x(12-x).\nA'=12-2x=0 at 6.\nA''=-2; endpoint areas are 0.\nMaximum area is 36.");

DETAIL(ocr_calc_4,
 "A polynomial antiderivative raises each power by one and divides by the new power. Add +C to an indefinite result.",
 "A definite integral is F(upper)-F(lower). Reversing the limits reverses its sign.",
 "Area below the x-axis contributes negative integral. Split at zeros and add positive magnitudes for geometric area.",
 "For area between curves find intersection limits and integrate the upper function minus the lower one.",
 "Evaluate a definite integral","Integral of 2x+3 from 1 to 4.\nF(x)=x^2+3x.\nF(4)=28, F(1)=4.\nResult: 24.",
 "Area between line and square","y=x and y=x^2 meet at 0 and 1.\nBetween them x is above x^2.\nIntegral of x-x^2 gives [x^2/2-x^3/3] from 0 to 1 = 1/6.");

DETAIL(ocr_calc_5,
 "Displacement is signed position change. Its derivative is velocity and the next derivative is acceleration.",
 "Integrate acceleration for velocity, then velocity for displacement. Each integration introduces a constant.",
 "Use given initial velocity and displacement to determine those constants.",
 "Distance travelled can exceed displacement. Split the motion at times where velocity changes sign.",
 "Recover velocity and displacement","a=4t, v(0)=3, s(0)=2.\nv=2t^2+3.\ns=(2/3)t^3+3t+2.\nAt t=3, s=29.",
 "Distance with a reversal","v=2t-4 from t=0 to 3.\nIt changes sign at 2. Take F=t^2-4t.\nF(0)=0, F(2)=-4, F(3)=-3.\nDistance=4+1=5.");

DETAIL(ocr_numerical_1,
 "Opposite signs bracket a root only if the function is continuous on the interval.",
 "Bisect by testing the midpoint. Replace the endpoint with the same sign as that midpoint.",
 "For iteration rewrite as x=g(x), then use the most recent estimate. A poor rearrangement can diverge.",
 "Quote a root to a precision only when the bracket or repeated values support it. Check the residual in the original equation.",
 "Two bisections for sqrt(5)","f=x^2-5. f(2)<0 and f(3)>0.\nf(2.5)=1.25>0, so use (2,2.5).\nf(2.25)=0.0625>0.\nRoot now bracketed by 2 and 2.25.",
 "Fixed-point steps","Iterate x(n+1)=sqrt(2+x(n)) from x(0)=1.\nx(1)=1.7321; x(2)=1.9319; x(3)=1.9829.\nThe positive fixed point solves x^2=x+2, giving 2.");

DETAIL(ocr_numerical_2,
 "A secant gradient between two points estimates the local tangent gradient.",
 "Use (y2-y1)/(x2-x1) with both coordinates in their correct order.",
 "Moving both points toward the target usually improves the estimate for a smooth curve. A centred chord can reduce bias.",
 "A large gap can hide curvature. Very small gaps with rounded y-values can amplify measurement error.",
 "Estimate slope from a chord","For y=x^2 near x=3, take x=3 and 3.1.\nThe y-values are 9 and 9.61.\nChord gradient=0.61/0.1=6.1.",
 "Improve a gradient estimate","For y=x^3 near x=1, use 0.9 and 1.1.\ny=0.729 and 1.331.\nGradient=0.602/0.2=3.01.\nExact slope at 1 is 3.");

DETAIL(ocr_numerical_3,
 "For equally spaced x-values, multiply h/2 by the first and last heights plus twice the inner heights.",
 "h=(b-a)/n for n strips, so there are n+1 ordinates.",
 "For a convex graph, chords lie above the curve and give an overestimate. For concave graphs the reverse holds.",
 "Using more strips often improves the estimate. If the graph crosses the axis, signed and geometric area differ.",
 "Two trapezia","x=0,1,2; heights 2,3,6.\nh=1. The inner height 3 belongs to both trapezia.\nEstimate=(1/2)(2+2*3+6)=7.",
 "Compare with exact area","For y=x^2 on [0,2], heights 0,1,4 at unit steps.\nTrapezia give (0+2+4)/2=3.\nExact integral=8/3. Convexity explains the overestimate.");

DETAIL(ocr_exponent_1,
 "An exponential model changes by the same factor over each equal interval: y=A*b^t.",
 "A rise of r% uses b=1+r/100. A fall uses b=1-r/100.",
 "Use a logarithm to find time when the target and multiplier are known.",
 "Interpret parameters and avoid extrapolating a model beyond plausible conditions.",
 "Decay after several periods","A quantity starts at 500 and falls 12% yearly.\nAfter 3 years: 500*0.88^3=340.736.\nAbout 341 units.",
 "Find the first year above a target","100 grows by 8% annually.\n100*1.08^n>150 gives n>ln(1.5)/ln(1.08)=5.27...\nFirst whole year: 6.");

DETAIL(ocr_exponent_2,
 "For y=k*a^x, plotting log y against x makes a straight line with intercept log k and gradient log a.",
 "For y=k*x^n, plot log y against log x. The gradient is n and intercept is log k.",
 "Recover k and a with the inverse log in the base used by the graph.",
 "The logged quantities must be positive. Read intercepts on the transformed axes.",
 "Find an exponential model","Plot log10 y against x. Slope 0.3, intercept 1.\nk=10^1=10; a=10^0.3.\nModel: y=10*(10^0.3)^x.",
 "Find a power model","Plot ln y against ln x. Slope -2, intercept ln 5.\nn=-2 and k=5.\ny=5/x^2 for x>0.");

DETAIL(ocr_exponent_3,
 "log_b(x) is the exponent on b giving x. Require x>0 and a positive base other than 1.",
 "Product, quotient and power rules turn multiplication, division and powers inside a logarithm into sums, differences and multiples.",
 "To solve a^x=b, take logs in any convenient base and divide by log a.",
 "Check each candidate against all original logarithm domains. Negative inputs cannot be rescued by later algebra.",
 "Solve an exponential equation","5^(2x-1)=12.\n(2x-1)ln 5=ln 12.\nx=(1+ln 12/ln 5)/2, about 1.272.",
 "Use a log law and domain","log10(x)+log10(x-9)=1.\nDomain x>9. Combine to x(x-9)=10.\n(x-10)(x+1)=0.\nOnly x=10 is valid.");

DETAIL(al_proof_1,"Deduction starts with stated facts and shows each implication. Use n=2k or 2k+1 for parity.","Exhaustion checks every case in a finite complete list. Explain why no case is missing.","Contradiction assumes the opposite of the claim and derives a conflict.","One valid counterexample disproves a universal statement. Examples alone do not prove it.",
 "Prove divisibility by 3","The product n(n+1)(n+2) uses three consecutive integers.\nTheir remainders modulo 3 are 0,1,2 in some order.\nOne factor is divisible by 3, so the product is too.",
 "Disprove a prime claim","Claim: n^2+n+41 is prime for every positive integer n.\nSet n=41.\n41^2+41+41=41*43.\nIt is composite, so the claim is false.");

DETAIL(al_algebra_1,"For positive a use a^(p/q) as the qth root of a^p. Negative powers invert the value.","Simplify surds before collecting terms. Use a conjugate for a two-term surd denominator.","Use polynomial division with descending powers and omitted zero coefficients inserted.","f(c)=0 tests x-c as a factor. In division by x-c the remainder is f(c).",
 "Rationalise a conjugate","Multiply top and bottom by sqrt(5)+2.\nDenominator=(sqrt(5))^2-2^2=1.\nAnswer: sqrt(5)+2.",
 "Divide out a factor","f=2x^3-x^2-8x+4; f(2)=0.\nDivide by x-2 to obtain 2x^2+3x-2.\nThen f=(x-2)(2x-1)(x+2).");

DETAIL(al_algebra_2,"D=b^2-4ac determines the number of real roots. A repeated root gives a tangency or a double factor.","Completing the square gives the vertex and supplies a method for deriving the quadratic formula.","For a disguised quadratic choose a substitution that covers the repeated powers and state its range.","When squaring or changing variable, substitute back and reject roots outside the original domain.",
 "Find a parameter for tangency","x^2-6x+k=0 has one repeated root.\nD=36-4k=0.\nk=9; the repeated root is 3.",
 "Disguised quadratic in x^2","x^4-5x^2+4=0.\nSet u=x^2, so (u-1)(u-4)=0.\nu=1 or 4.\nx=-2,-1,1,2.");

DETAIL(al_algebra_3,"Use roots, poles and interval signs for a rational inequality. Multiplying by an unknown-sign denominator can reverse it.","A strict inequality excludes roots. A denominator zero is always excluded.","For |f(x)|<a with a>0, solve -a<f(x)<a. For |f(x)|>a, solve the two outside cases.","For intersections of modulus graphs, split at points where the expression inside a modulus changes sign.",
 "Rational sign chart","(x-1)/(x+2)>0.\nCritical values -2 and 1. Test -3,0,2 to get signs +,-,+.\nAnswer: x<-2 or x>1.",
 "Modulus inequality","|3x+2|>=5 means 3x+2>=5 or 3x+2<=-5.\nAnswer: x>=1 or x<=-7/3.");

DETAIL(al_algebra_4,"Track domains and ranges before composing or inverting. The inner function's output must fit the outer domain.","An inverse is the reflection in y=x. Restrict a many-to-one function to a suitable branch first.","f(kx) scales horizontally by 1/|k|; kf(x) scales vertically by |k|. A negative k adds a reflection.","|f(x)| reflects negative outputs above the axis; f(|x|) copies the nonnegative-input half to the other side.",
 "Transform a parabola","f=x^2. For 3f(2(x-1))-4, compress horizontally by 1/2, shift right 1, stretch vertically by 3, then shift down 4.\nEquation: y=12(x-1)^2-4.",
 "Inverse of a rational function","y=(2x+1)/(x-3).\nyx-3y=2x+1, so x=(3y+1)/(y-2).\nInverse: (3x+1)/(x-2), x!=2.");

DETAIL(al_algebra_5,"A proper fraction has numerator degree below denominator degree. Use division first if it is improper.","For distinct linear factors give each its own constant numerator. For a repeated linear factor include every power up to its multiplicity.","Multiply through by the denominator. Substitute roots to isolate constants, then compare coefficients as needed.","Recombine to check. Preserve all restrictions from the original denominator.",
 "Two distinct factors","(5x+1)/((x-1)(x+2))=A/(x-1)+B/(x+2).\nAt x=1: 6=3A. At x=-2: -9=-3B.\nAnswer: 2/(x-1)+3/(x+2).",
 "Repeated factor","(3x+7)/(x+2)^2=A/(x+2)+B/(x+2)^2.\n3x+7=A(x+2)+B.\nA=3, B=1.");

DETAIL(al_coord_1,"A straight line can be written y=mx+c or ax+by+c=0. A vertical line needs x=constant.","Use changes in coordinates for direction and average coordinates for midpoint.","Equal finite gradients give parallel lines. Negative reciprocals give perpendicular non-axis-aligned lines.","Use an intersection as a simultaneous solution. In modelling, explain what the gradient and intercept represent.",
 "Perpendicular bisector","A=(0,2), B=(6,4). Midpoint=(3,3).\nAB gradient=1/3; perpendicular gradient=-3.\nEquation y-3=-3(x-3), so y=-3x+12.",
 "Intersection of two lines","y=3x+1 and 2x+y=16.\nSubstitute to get 5x=15.\nx=3, y=10.\nIntersection (3,10).");

DETAIL(al_coord_2,"A circle has centre (a,b) and radius r in (x-a)^2+(y-b)^2=r^2.","Complete squares in both variables for an expanded circle equation.","A tangent is perpendicular to the radius at the contact point. Handle horizontal and vertical lines separately.","Substitute a line into the circle. The discriminant distinguishes two intersections, tangency and no real intersection.",
 "Find centre and radius","x^2+y^2+6x-4y-12=0.\n(x+3)^2+(y-2)^2=12+9+4=25.\nCentre (-3,2), radius 5.",
 "Tangent to a circle","Centre (2,-1), contact (5,3).\nRadius gradient=4/3, tangent gradient=-3/4.\nEquation y-3=-(3/4)(x-5).");

DETAIL(al_coord_3,"A parameter specifies x and y together. Its range can restrict the Cartesian curve.","Eliminate the parameter using substitution or an identity. Preserve the domain and trace direction.","Find intersections by requiring both coordinates to agree; different curves can use different parameter values.","For a parametric tangent use (dy/dt)/(dx/dt), where the denominator is nonzero.",
 "Eliminate the angle","x=3cos t, y=2sin t, 0<=t<2pi.\n(x/3)^2+(y/2)^2=cos^2 t+sin^2 t=1.\nThis is a complete ellipse.",
 "Keep the restricted branch","x=t^2, y=t+1 for t>=0.\nt=y-1, hence x=(y-1)^2.\nThe condition gives y=1+sqrt(x) for x>=0.");

DETAIL(al_series_1,"Arithmetic terms have constant difference d: u(n)=a+(n-1)d.","The sum is n/2 times first plus last, or n/2 times 2a+(n-1)d.","Use differences between the given term indices to recover d.","For a threshold, solve an inequality for n and check neighbouring whole numbers.",
 "Recover a and d","u(4)=17 and u(9)=37.\n5d=20, d=4.\na=17-3*4=5.\nS(9)=9(5+37)/2=189.",
 "First total over 100","Sequence 3,5,7,... gives S(n)=n(n+2).\nS(9)=99, S(10)=120.\nFirst total over 100 is at n=10.");

DETAIL(al_series_2,"The geometric nth term is a*r^(n-1). Ratios of adjacent nonzero terms give r.","For r!=1, S(n)=a(1-r^n)/(1-r). For r=1 use n*a.","The infinite sum exists if |r|<1 and equals a/(1-r). Negative ratios alternate signs.","When recovering r from nonadjacent terms, consider multiple roots if the exponent is even.",
 "Finite geometric sum","a=3, r=2, n=6.\nS(6)=3(1-2^6)/(1-2)=3*63.\nThe six terms are 3,6,12,24,48,96.\nAnswer: 189.",
 "Find a ratio from a limit","First term 12 and sum to infinity 20.\n12/(1-r)=20, so 1-r=0.6.\nr=0.4, which satisfies |r|<1.");

DETAIL(al_series_3,"For positive integer n, the binomial expansion is finite. Select the coefficient using nCr.","For general n, use coefficients n(n-1)...(n-r+1)/r!. Apply the expansion only when |u|<1 for (1+u)^n.","Factor out the constant first in (a+bx)^n; it multiplies the entire expansion.","Keep only terms needed for the requested coefficient or approximation. State the interval of validity.",
 "Square root expansion","sqrt(1+4x) = 1+(1/2)(4x)+((1/2)(-1/2)/2)(4x)^2+...\nAnswer: 1+2x-2x^2+..., |x|<1/4.",
 "Coefficient in a product","Find the x^2 coefficient in (1+x)(1-2x)^4.\nFirst three terms of second factor: 1-8x+24x^2.\nCoefficient=24-8=16.");

DETAIL(al_trig_1,"Radians measure arc length divided by radius. Convert degrees by multiplying by pi/180.","With theta in radians, s=r*theta and sector area=0.5*r^2*theta.","A segment is formed by an arc and chord. Subtract the included triangle for a minor segment.","Use radians in differentiation and integration of trig functions unless a different convention is explicitly required.",
 "Arc and sector area","r=12 cm, angle 75 degrees=5pi/12.\nArc=12*5pi/12=5pi cm.\nArea=0.5*144*5pi/12=30pi cm^2.",
 "Find angle from arc","An arc of length 9 cm has radius 6 cm.\nTheta=9/6=1.5 radians.\nSector area=0.5*36*1.5=27 cm^2.");

DETAIL(al_trig_2,"Use reciprocals sec=1/cos, cosec=1/sin and cot=1/tan where defined.","Use principal inverse domains and then periodicity to get all solutions. For tan the period is pi.","For a scaled angle multiply the interval first. Avoid dividing by a trig factor that could be zero.","Remember sec^2 x=1+tan^2 x and cosec^2 x=1+cot^2 x.",
 "Solve a scaled cosine","cos(2x)=1/2 for 0<=x<pi.\nIn 0<=2x<2pi, 2x=pi/3 or 5pi/3.\nx=pi/6 or 5pi/6.",
 "Keep zero-factor roots","sin x cos x=sin x/2 on [0,2pi).\nFactor sin x*(cos x-1/2)=0.\nSolutions: 0, pi/3, pi, 5pi/3.");

DETAIL(al_trig_3,"Use the addition formulae with careful signs. In cos(A+B) the sine product is subtracted.","Double-angle identities include sin 2x=2sin x cos x and cos 2x=2cos^2 x-1=1-2sin^2 x.","For a sin x+b cos x, R=sqrt(a^2+b^2). Match coefficients with R sin(x+alpha).","Choose the correct quadrant for the phase. The resulting expression has range [-R,R] for unrestricted x.",
 "Exact value of sin 75","sin(45+30)=sin45 cos30+cos45 sin30.\nAnswer: (sqrt(6)+sqrt(2))/4.",
 "Rewrite in R form","For 5 cos x-12 sin x use 13 cos(x+a).\n13cos a=5, 13sin a=12.\na=atan(12/5) in the first quadrant.\nMaximum value is 13.");

DETAIL(al_trig_4,"A sinusoid has form midline + amplitude*cos(k(t-shift)); period = 2pi/|k|.","Compute midline and amplitude from maxima and minima; use the time of a peak to set the phase.","When solving for a time, seek all roots in the specified period. Reject times outside the model interval.","For non-right triangles, use sine rule for opposite pairs and cosine rule for included-angle information.",
 "Build a tide model","Depth max 9 m, min 3 m, period 8 h, high tide t=2.\nMidline=6, amplitude=3, k=pi/4.\nD=6+3cos((pi/4)(t-2)).",
 "Time on a rising cycle","D=4+2sin(pi*t/6) for 0<=t<=6.\nD=5 gives sin(pi*t/6)=1/2.\nAngles pi/6 and 5pi/6 give t=1 or 5.");

DETAIL(al_logs_1,"ln is the inverse of exp. ln ab=ln a+ln b for positive a,b, and ln(a^n)=n ln a.","The model y=Ae^(kt) has initial value A; positive k gives growth and negative k decay.","For a time interval T, the multiplier is e^(kT). This relates continuous and discrete growth.","Return to the original equation to check domain after using logarithm laws.",
 "Find a half-life","y=80e^(-0.12t). Set y=40.\ne^(-0.12t)=1/2.\nt=ln 2/0.12, about 5.78 time units.",
 "Determine a growth rate","A population starts at 200 and reaches 350 after 4 years.\n350=200e^(4k).\nk=ln(1.75)/4, about 0.1399 per year.");

DETAIL(al_logs_2,"For y=Ae^(kx), plot ln y against x. Slope is k; intercept is ln A.","For y=Ax^n, plot ln y against ln x. Slope is n; intercept is ln A.","For a base-10 graph, use powers of 10 when undoing log10. The exponential slope there is k/ln 10.","Interpret residuals and model limitations. A linear trend on transformed axes is evidence for a model, within the observed range.",
 "Exponential from a fitted line","A line for ln y against x is ln y=1.4-0.3x.\nA=e^1.4, k=-0.3.\nModel y=e^1.4*e^(-0.3x).",
 "Recover a power law","Log10 y=0.6+1.5 log10 x.\ny=10^0.6*x^1.5 for x>0.\nDoubling x multiplies y by 2^1.5.");

DETAIL(al_diff_1,"Use chain rule for a composition: differentiate the outer expression, then multiply by the inner derivative.","Use (uv)'=u'v+uv'; for a quotient use (u'v-uv')/v^2.","Standard trig derivatives use radians. d/dx ln u = u'/u for u>0.","State relevant domains and simplify only after applying the correct rule.",
 "Product and chain rules","y=x^2*cos(3x).\nDerivatives: 2x and -3sin(3x).\ny'=2x*cos(3x)-3x^2*sin(3x).",
 "Differentiate a quotient","y=(x+1)/(x^2+1).\ny'=[(x^2+1)-2x(x+1)]/(x^2+1)^2.\nAnswer: (1-2x-x^2)/(x^2+1)^2.");

DETAIL(al_diff_2,"Treat y as a function of x in implicit differentiation. A derivative of y^n gains a factor dy/dx.","If terms contain x and y together, use the product rule as well.","Collect dy/dx terms and solve for it; watch where its denominator vanishes.","For parametric curves dy/dx=(dy/dt)/(dx/dt). Differentiate the ratio in t and divide by dx/dt again for the second derivative.",
 "Implicit product","Differentiate x*y+y^2=10.\ny+x*y'+2y*y'=0.\ny'=-y/(x+2y) where x+2y!=0.",
 "Parametric tangent slope","x=t^2+1, y=t^3.\ndx/dt=2t, dy/dt=3t^2.\nAt t=2, point (5,8), slope=3.\nTangent y-8=3(x-5).");

DETAIL(al_diff_3,"Set f'=0 for stationary points. A derivative may also be undefined at other extrema.","Use sign of f'' at a stationary point for classification when nonzero; otherwise check f' on either side.","Concavity follows the sign of f''. An inflection needs a change of concavity, not merely f''=0.","For global extrema on a closed interval, compare all candidate values with the endpoints.",
 "Stationary inflection","f=x^3. At x=0, f'=0 and f''=0.\nf'=3x^2 is positive on both sides, so no extremum.\nf''=6x changes sign, giving an inflection.",
 "Maximum on a domain","f=x^3-3x on [0,2].\nf'=3x^2-3=0 at x=1.\nValues f(0)=0, f(1)=-2, f(2)=2.\nMaximum is 2 at x=2.");

DETAIL(al_diff_4,"Relate quantities with an equation before differentiating with respect to time.","The chain rule connects rates such as dV/dt=(dV/dr)*(dr/dt). Substitute given values after differentiating.","For optimisation state the physical domain, find critical points and check their nature and the endpoints.","Check units: for example a volume changing with time has units cm^3/s.",
 "Expanding sphere","V=(4/3)pi*r^3, dr/dt=0.2 cm/s.\ndV/dt=4pi*r^2*dr/dt.\nAt r=5 cm, dV/dt=20pi cm^3/s.",
 "Minimise a rectangle perimeter","Area=36, so other side=36/x and P=2x+72/x.\nP'=2-72/x^2=0 at x=6. P''=144/x^3>0 for x>0.\nMinimum perimeter=24.");

DETAIL(al_integral_1,"Reverse the power rule with x^(n+1)/(n+1) except at n=-1, which gives ln|x|.","In substitution let u=g(x) and replace g'(x)dx by du. Rewrite every remaining factor in u.","For a definite integral either change both bounds to u or substitute back before evaluating in x.","For exp, sine and cosine of a linear argument, divide the standard primitive by the inner coefficient.",
 "Change bounds in a substitution","Integrate 2x/(1+x^2) from 0 to 2.\nu=1+x^2, du=2x dx. Bounds 1 and 5.\nIntegral of 1/u gives ln 5.",
 "Integrate a trig composition","In radians, integrate 6cos(3x-1).\nThe primitive of cos is sin. Divide by inner gradient 3.\nAnswer: 2sin(3x-1)+C.");

DETAIL(al_integral_2,"A definite integral is signed. For total area split at roots and add absolute contributions.","Between curves find intersections, determine which graph is above in each interval, and integrate their difference.","Use exact values of limits and antiderivatives when possible. Include area units for modelling.","A reversed interval changes the integral's sign. A symmetric integral of an odd function is zero.",
 "Total area across a root","y=x-1 from x=0 to 3.\nSplit at 1. Two triangular areas are 1/2 and 2.\nTotal area=5/2; signed area=3/2.",
 "Area between a parabola and line","y=4x and y=x^2 meet at 0 and 4.\nArea=[2x^2-x^3/3] from 0 to 4.\nAnswer: 32/3.");

DETAIL(al_integral_3,"Integration by parts follows from the product rule: integral u dv = uv - integral v du.","Choose u so its derivative simplifies and choose dv you can integrate immediately.","Logarithms often serve as u; for a product such as x exp(x), choose the polynomial as u.","For repeated applications track the signs. For a definite integral evaluate the entire bracket at both bounds.",
 "Integrate ln x","Use u=ln x and dv=dx.\ndu=dx/x, v=x.\nIntegral=x ln x-integral(1)dx.\nAnswer: x ln x-x+C, x>0.",
 "Definite product integral","Integrate x*cos x from 0 to pi.\nu=x, v=sin x.\nPrimitive=x*sin x+cos x.\nAt pi it is -1; at 0 it is 1. Result=-2.");

DETAIL(al_integral_4,"Make the rational function proper by polynomial division before decomposing it.","Decompose into simpler fractions with distinct or repeated linear terms. Check the constants by recombining.","Use integral 1/(ax+b) = ln|ax+b|/a and use the power rule for degree -2 or below.","A definite interval cannot cross a pole for ordinary evaluation by a single antiderivative.",
 "Distinct linear factors","Integrate 3/((x-1)(x+2)).\nDecompose as 1/(x-1)-1/(x+2).\nAnswer: ln|x-1|-ln|x+2|+C.",
 "Repeated linear factor","(2x+7)/(x+3)^2=2/(x+3)+1/(x+3)^2.\nIntegrate each separately.\nAnswer: 2ln|x+3|-1/(x+3)+C.");

DETAIL(al_integral_5,"For a separable equation dy/dx=f(x)g(y), divide by g(y) where nonzero and integrate both sides.","Check separately for equilibrium solutions lost when dividing by g(y).","Use initial data to find the constant and the correct branch. State the valid interval if the formula has a pole.","In a growth law dy/dt=k*y, exp appears because the integral of 1/y is ln|y|.",
 "Decay to an equilibrium","dy/dt=-2(y-5), y(0)=9.\nln|y-5|=-2t+C.\ny=5+4e^(-2t).\nCheck the initial value and long-term limit 5.",
 "Separate a quadratic rate","dy/dx=y^2, y(0)=2.\nIntegrate y^-2: -1/y=x+C.\nC=-1/2, so y=2/(1-2x) on the branch x<1/2.");

DETAIL(al_integral_6,"Replace dx with x'(t)dt when integrating under a parametric curve.","Find t values at geometric boundaries. Check the direction in which x moves.","For area use the positive contribution; split at a change of orientation or where y changes sign.","Where two branches share x, integrate upper branch minus lower branch or work on each branch separately.",
 "Integrate with x=t^3","x=t^3, y=t^2, 0<=t<=2.\ndx/dt=3t^2. Integral of 3t^4 from 0 to 2 is 3*32/5.\nArea=96/5.",
 "Reverse parameter direction","x=4-t, y=t^2, 0<=t<=2.\nAs t increases x decreases; dx/dt=-1.\nSigned integral=-8/3.\nGeometric area between x=2 and 4 is 8/3.");

DETAIL(al_numerical_1,"A sign change brackets at least one zero only when f is continuous. An even-multiplicity root may not change sign.","Arrange x=g(x), choose a start near the root, and use full precision at each iteration.","Near a fixed point, |g'(x)|<1 typically gives local convergence. A negative derivative may make estimates alternate.","Check rounding with an interval or stability plus a small residual. A sign change at a pole gives no root.",
 "Bracket a cubic root","f=x^3-x-1.\nf(1.3)=-0.103, f(1.4)=0.344.\nf(1.35)=0.110375.\nRoot lies between 1.30 and 1.35.",
 "Use a convergent rearrangement","For x^3=x+1 use x(n+1)=(x(n)+1)^(1/3).\nFrom 1, first estimates 1.2599, 1.3123, 1.3224.\nThe positive root is near 1.3247.");

DETAIL(al_numerical_2,"Newton-Raphson uses the tangent intercept: x(n+1)=x(n)-f(x(n))/f'(x(n)).","Substitute into f and f' at the same current estimate. Keep unrounded values internally.","A zero or very small derivative or a poor start can cause failure or convergence to a different root.","Check final residual and required precision. Use a bracket when you need assurance of which root is intended.",
 "Newton approximation to sqrt(7)","Use f=x^2-7, f'=2x, x0=3.\nx1=3-2/6=8/3.\nx2=8/3-((8/3)^2-7)/(16/3)=127/48, about 2.6458.",
 "Identify a failure","For f=x^3-2x+2 start x0=0.\nf(0)=2, f'(0)=-2 gives x1=1.\nf(1)=1, f'(1)=1 gives x2=0.\nThe iteration cycles.");

DETAIL(al_numerical_3,"For n equally spaced strips use h=(b-a)/n and multiply h/2 by the weighted sum of ordinates.","Count the first and last heights once and the interior heights twice.","Determine overestimate or underestimate from the curve's convexity on the interval.","A finer grid normally helps smooth curves. Signed estimates need splitting if the question asks for geometric area.",
 "Three-strip estimate","Estimate integral of y=x^2 from 0 to 3 with h=1.\nHeights 0,1,4,9.\nT=(0+2*1+2*4+9)/2=9.5. Exact is 9.",
 "Explain an underestimate","y=sqrt(x) on [0,4], with h=2.\nT=(0+2sqrt(2)+2)*1, about 4.83.\nThe curve is concave, so the chords lie below it.");

DETAIL(al_vectors_1,"A vector is a displacement with components. AB=OB-OA and reversing a vector negates each component.","Its magnitude is the square root of the sum of squared components. Divide by magnitude for a unit vector.","Add like components or multiply each component by a scalar. Parallel nonzero vectors are scalar multiples.","Distinguish position vectors from displacements. A point division uses a fraction of the displacement from one endpoint.",
 "Length and unit direction","A=(1,0,-2), B=(3,3,4).\nAB=(2,3,6), length=sqrt(4+9+36)=7.\nUnit vector is (2/7,3/7,6/7).",
 "Point dividing a segment","A=(1,2,3), B=(7,5,-3). P is one third from A to B.\nAB=(6,3,-6).\nP=A+AB/3=(3,3,1).");

DETAIL(al_vectors_2,"Represent sides and diagonals as differences of position vectors.","Show parallelism by exhibiting a scalar multiple. With a shared point this also proves collinearity.","Equate components or coefficients in independent directions to solve unknown scalars.","Equal magnitudes alone do not imply equal or parallel vectors. For geometry proofs say what the relation establishes.",
 "Prove the shape a parallelogram","A=(0,0,0), B=(2,1,1), D=(1,3,-1), C=(3,4,0).\nAB=DC=(2,1,1); AD=BC=(1,3,-1).\nOpposite sides are parallel and equal.",
 "Find an unknown for parallel sides","AB=(2,k,4), CD=(-1,3,-2).\nAB=-2CD by the first and third components.\nSecond component gives k=-6.");

DETAIL(al_sampling_1,"Distinguish population, sample and sampling frame. A biased frame can omit part of the population.","A simple random sample gives equally likely subsets of the chosen size. A systematic sample uses a random start then a fixed interval.","For stratified sampling allocate proportionally and select randomly within each group. Quota counts alone do not imply random choice.","Choose a method that fits the available list, practical costs and risk of bias, and evaluate non-response.",
 "Allocate strata","Population groups 120 and 80; sample 30.\nFirst group: 30*120/200=18.\nSecond group: 12. Select randomly within each.",
 "Systematic sampling","A list of 240 is sampled for 20 entries.\nStep=12; random start 7.\nSelect 7,19,31,...,235.\nA repeating pattern every 12 could bias it.");

DETAIL(al_sampling_2,"Read the data dictionary for variable definitions, locations, dates, units and missing-value codes.","Check whether trace values mean a real but unmeasurably small value. Missing observations are different from zero.","Respect categorical data such as compass direction. Compare appropriate seasons or locations for weather variables.","Interpret any finding in context and state coverage and data limitations before extrapolating.",
 "Handle missing and trace rain","Rainfall readings are 0, a trace, 2.4 mm and missing.\nFor the mean, exclude missing data. If traces are treated as zero, say so.\nMean then 2.4/3=0.8 mm.",
 "Compare months fairly","When comparing two sites in July, restrict both samples to July and use the same years where possible.\nThis controls season and reduces confounding by year.");

DETAIL(al_data_1,"For a histogram height=frequency density and area=frequency. Equal-width bars need no density adjustment for relative shape.","A box plot compares quartiles and range. Use a stated outlier rule consistently.","Compare centre, spread and skew in context. Use median/IQR when extremes or skew make them more representative.","A scatter plot can show strength and direction of association. Correlation does not establish causation.",
 "Density to frequency","A class from 10 to 18 has frequency density 2.75.\nWidth 8 times 2.75 gives frequency 22.",
 "Identify an outlier","Q1=7, Q3=19, so IQR=12.\nUpper fence=19+1.5*12=37.\nA value 41 is an upper outlier. The fence itself is not an outlier.");

DETAIL(al_data_2,"For a population-style dataset variance=mean(x^2)-mean(x)^2. Standard deviation is its positive square root.","For repeated values, weight both sums by frequency. A grouped version uses midpoints and is an estimate.","If y=a+bx then mean(y)=a+b*mean(x), variance(y)=b^2*variance(x), and SD(y)=|b|*SD(x).","Keep enough precision during subtraction and check that variance is nonnegative.",
 "Calculate variance and SD","Data 2,4,6. Mean=4.\nMean of squares=(4+16+36)/3=56/3.\nVariance=56/3-16=8/3.\nSD=sqrt(8/3).",
 "Undo coding","Let y=(x-10)/3. Mean(y)=4, SD(y)=2.\nx=10+3y.\nMean(x)=22, SD(x)=6, variance(x)=36.");

DETAIL(al_probability_1,"Conditional probability restricts the sample space: P(A|B)=P(A and B)/P(B), for positive P(B).","Multiply in the reverse direction to get P(A and B)=P(B)*P(A|B).","Independence gives P(A and B)=P(A)P(B); mutually exclusive events with positive chances are dependent.","Use the total probability of the observed outcome in the denominator for a reverse condition.",
 "Compute a conditional probability","P(A and B)=0.18 and P(B)=0.3.\nGiven B, only its 0.3 share of outcomes is relevant.\nP(A|B)=0.18/0.3=0.6.",
 "Reverse a condition","60% use A, 40% B; pass rates 0.8 and 0.5.\nP(pass)=0.6*0.8+0.4*0.5=0.68.\nP(A|pass)=0.48/0.68=12/17.");

DETAIL(al_probability_2,"For a union add the two probabilities and subtract their overlap. A complement uses 1 minus the event.","Keep mutually exclusive and independent separate. Check a tree's branch probabilities sum to 1 at each node.","Multiply along each path and add disjoint paths. In sampling without replacement update the second branch.","A Venn diagram or two-way table can infer intersection counts and show which denominator a conditional probability needs.",
 "Find a union and neither","P(A)=0.45, P(B)=0.4, P(both)=0.15.\nUnion=0.45+0.4-0.15=0.70.\nNeither=0.30.",
 "Tree without replacement","Bag 4 green, 2 white. Two draws.\nP(two same)=(4/6)(3/5)+(2/6)(1/5)=7/15.\nP(different)=8/15.");

DETAIL(al_dist_1,"The binomial model has fixed n, independent trials and constant success probability p.","P(X=r)=nCr*p^r*(1-p)^(n-r). Mean=np and variance=np(1-p).","Use cumulative probabilities for ranges. At least k equals 1-P(X<=k-1).","Check support 0<=r<=n and assumptions in context; unequal probabilities or dependent trials can invalidate the model.",
 "Exactly two","X~B(5,0.3).\nChoose two successes in 5C2=10 ways.\nMultiply each path probability by 10: 10*(0.3)^2*(0.7)^3.\nAnswer: 0.3087.",
 "At least one","X~B(6,0.1).\nP(X>=1)=1-0.9^6=0.468559.\nMean=0.6 and variance=0.54.");

DETAIL(al_dist_2,"For X~N(mu,sigma^2), convert to Z=(X-mu)/sigma. The second parameter is the variance.","Use left-tail values, complements for right tails, and differences for intervals.","For a percentile find z from the required cumulative probability, then use x=mu+sigma*z.","The distribution is continuous and symmetric about mu. One exact value has probability zero, so including interval endpoints does not affect the result.",
 "Normal right tail","X~N(50,4^2). Find P(X>56).\nz=(56-50)/4=1.5.\nP(Z>1.5)=1-0.9332=0.0668.",
 "Use a percentile","X~N(100,15^2). The 90th percentile of Z is about 1.2816.\nx=100+15*1.2816.\nPercentile is about 119.2.");

DETAIL(al_testing_1,"State H0 with an exact p and H1 with the correct tail or two-sided alternative.","Under H0 model the success count as binomial. Include the observed result in a tail probability.","Compare the p-value with the significance level, or use the specified critical region. For a two-tailed critical region, allocate significance between the tails.","Conclude in context. Failing to reject means insufficient evidence for H1.",
 "Test an increased success rate","H0:p=0.5, H1:p>0.5. Observe 8 successes in 9.\nP(X>=8)=(9+1)/512=0.01953.\nReject H0 at 5%; evidence that p increased.",
 "No significant decrease","H0:p=0.4, H1:p<0.4. Observe 0 in 5.\nP(X<=0)=0.6^5=0.07776.\nAt 5%, fail to reject H0.");

DETAIL(al_testing_2,"For a known population SD use z=(sample mean-mu0)/(sigma/sqrt(n)) under H0 when the normal model applies.","Set hypotheses about population mean or population correlation, with the tail dictated by the claim.","For correlation use the supplied critical value and the appropriate sign or absolute value. For a normal mean compute the relevant tail.","Use evidence rather than proof language. Where assumptions matter, identify independence, model form or how the sample was obtained.",
 "One-sided mean test","H0:mu=20, H1:mu>20, sigma=4, n=16, mean=22.\nz=2/1=2. One-sided p about 0.0228.\nReject at 5%; evidence the mean is above 20.",
 "Test a correlation","For a positive-tail test the given critical r is 0.632. Observed r=0.71.\nSince 0.71>0.632, reject H0 at the stated level.\nThere is evidence of positive correlation.");

DETAIL(al_units_1,"Use SI base units kg, m and s. Force in N is kg*m/s^2; a moment is measured in N m.","Convert km/h to m/s by dividing by 3.6. Convert units before substituting.","Choose directions and signs consistently for vector quantities. A negative result indicates the opposite direction.","Common models are particles, light strings, smooth surfaces and uniform rods. State what each assumption lets you ignore or infer.",
 "Convert and calculate momentum","A 900 kg car moves at 72 km/h.\n72/3.6=20 m/s.\nMomentum=900*20=18000 kg m/s.",
 "Use a modelling assumption","A light inextensible string links two objects.\nLight means its mass is ignored; inextensible means its ends have connected displacements.\nWith a smooth pulley the tension magnitude is equal on both sides.");

DETAIL(al_motion_1,"SUVAT applies only at constant acceleration. Choose a positive direction and keep signed components.","Pick the equation that excludes the unknown quantity you do not need. u is initial velocity and v final velocity.","Displacement and velocity are signed. Check times, turning points and physical limits separately.","If motion has different constant-acceleration phases, solve each phase with its own initial values.",
 "Stop under constant braking","u=18 m/s, v=0, a=-3 m/s^2.\nTime=(0-18)/(-3)=6 s.\nDistance=(18+0)*6/2=54 m.",
 "Find acceleration with no time","Speed increases from 4 to 10 m/s over 21 m in one direction.\n100-16=2*a*21.\na=2 m/s^2.");

DETAIL(al_motion_2,"Differentiate displacement for velocity and velocity for acceleration. Use integration in the reverse direction.","Initial conditions determine integration constants. Add them at each integration step.","For distance, split at sign changes of v and take magnitudes of displacement on every interval.","Interpret v-t gradients as acceleration and signed area as displacement.",
 "Integrate a time-dependent acceleration","a=6t-2, v(0)=1.\nv=3t^2-2t+1. Then s=t^3-t^2+t for s(0)=0.\nAt t=2, s=6 m.",
 "Find distance after a reversal","v=t^2-4 on [0,3]. It crosses zero at 2.\nF=t^3/3-4t.\nF(0)=0, F(2)=-16/3, F(3)=-3.\nDistance=16/3+7/3=23/3 m.");

DETAIL(al_motion_3,"Resolve initial velocity into u cos(theta) and u sin(theta) for a launch angle above horizontal.","Horizontal acceleration is zero; vertical acceleration is -g with up positive. Use the same time in each axis.","At maximum height vertical velocity is zero. Solve the vertical displacement for landing time, then use horizontal motion.","The familiar range formula assumes launch and landing heights match and air resistance is ignored.",
 "Horizontal launch","A ball leaves height 19.6 m horizontally at 6 m/s.\n19.6=0.5*9.8*t^2 gives t=2 s.\nHorizontal range=12 m.",
 "Peak height above launch","Vertical component u_y=14 m/s.\nAt the peak v_y=0.\n0=14^2-2*9.8*h, giving h=10 m.");

DETAIL(al_forces_1,"Draw the forces acting on the body. Resolve them along chosen perpendicular axes.","Apply resultant F=m*a in each direction. Weight is m*g vertically down, independent of slope.","In equilibrium net force is zero. An action-reaction pair acts on different bodies, so do not cancel it in one body's diagram.","Normal reaction acts perpendicular to the contact surface; tension acts along the string.",
 "Find acceleration","A 5 kg body has 28 N forwards and 8 N backwards.\nResultant=20 N forwards.\na=20/5=4 m/s^2 forwards.",
 "Reaction in a lift","A 60 kg person accelerates upward at 1.5 m/s^2.\nR-60*9.8=60*1.5.\nR=678 N.");

DETAIL(al_forces_2,"On an incline weight components are mg*sin(theta) along the slope and mg*cos(theta) perpendicular.","Friction opposes actual or impending relative motion. At limiting friction F=mu*R; otherwise static friction can be smaller.","Write separate equations for connected particles. A light inextensible string gives equal acceleration magnitudes.","With a smooth pulley and light string, tension is the same at both ends. Check signs and any motion assumption.",
 "Find limiting friction","A 4 kg block on a horizontal surface has mu=0.3.\nR=39.2 N. Maximum static friction=11.76 N.\nA horizontal force of 10 N is balanced by 10 N friction.",
 "Connected masses","3 kg and 2 kg hang over a smooth pulley.\n3g-T=3a and T-2g=2a. Add: g=5a.\na=1.96 m/s^2; T=2g+2a=23.52 N.");

DETAIL(al_moments_1,"Moment = force times perpendicular distance from pivot, with units N m.","Assign clockwise and anticlockwise signs. A force whose line of action meets the pivot has zero moment.","For a rigid body in equilibrium, both net force and net moment are zero.","Choose a pivot at an unknown force to remove that force from the moment equation. A uniform rod's weight acts at its midpoint.",
 "Balance a lever","30 N acts 0.4 m clockwise from the pivot.\nFor a force 0.6 m on the other side, F*0.6=30*0.4.\nF=20 N.",
 "Find two beam reactions","Uniform 4 m beam weighs 100 N. Extra 60 N lies 1 m from A.\nMoments at A: 4R_B=100*2+60*1=260.\nR_B=65 N; R_A=160-65=95 N.");

#undef DETAIL
